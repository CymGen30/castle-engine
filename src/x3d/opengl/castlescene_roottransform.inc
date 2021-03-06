{
  Copyright 2010-2019 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ TCastleRootTransform (with MainScene property that TCastleScene). }

{$ifdef read_interface}

type
  { Possible value of @link(TCastleRootTransform.UseHeadlight). }
  TUseHeadlight = (
    { Always show a headlight.
      The headlight properties (color, intensity, shape)
      are taken from @link(TCastleRootTransform.HeadlightNode). }
    hlOn,

    { Never show a headlight. }
    hlOff,

    { Show a headlight following the @link(TCastleRootTransform.MainScene)
      properties.

      If @link(TCastleRootTransform.MainScene) is @nil,
      there is no headlight.

      If @link(TCastleRootTransform.MainScene) is assigned,
      the headlight is shown if
      @link(TCastleSceneCore.HeadlightOn MainScene.HeadlightOn)
      is @true.
      @link(TCastleSceneCore.HeadlightOn MainScene.HeadlightOn) in turn
      is configutable, and by default looks at X3D NavigationInfo.headlight field.
      (If no NavigationInfo node is present, the headlight is shown,
      as NavigationInfo.headlight is @true by default.)

      The headlight properties (color, intensity, shape)
      follow @link(TCastleSceneCore.CustomHeadlight MainScene.CustomHeadlight),
      which can be customized in an X3D file using
      https://castle-engine.io/x3d_implementation_navigation_extensions.php#section_ext_headlight .
      If no @link(TCastleSceneCore.CustomHeadlight MainScene.CustomHeadlight)
      is set, we use @link(TCastleRootTransform.HeadlightNode). }
    hlMainScene
  );

  { Root of transformations and scenes (tree of TCastleTransform and TCastleScene). }
  TCastleRootTransform = class(TCastleAbstractRootTransform)
  strict private
    type
      TFreeNotificationProxy = class(TComponent)
        { Simply calls Owner.Notification(...). }
        procedure Notification(AComponent: TComponent; Operation: TOperation); override;
      end;
    var
      FMainScene: TCastleScene;
      { We register free notification of MainScene on MainSceneFreeNotificationProxy,
        not on Self.
        This way our RemoveFreeNotification doesn't accidentally remove the notification
        which should remain because of other reasons
        (when MainScene is our direct child, or when MainScene is part of our world,
        which is actually almost always the case). }
      MainSceneFreeNotificationProxy: TFreeNotificationProxy;
      FUseHeadlight: TUseHeadlight;
      FHeadlightNode: TAbstractLightNode;
    procedure SetMainScene(const Value: TCastleScene);
    procedure MainScene_BoundViewpointChanged(Sender: TObject);
    procedure MainScene_BoundViewpointVectorsChanged(Sender: TObject);
    procedure MainScene_BoundNavigationInfoChanged(Sender: TObject);
    function GetHeadlightNode: TAbstractLightNode;
    procedure SetHeadlightNode(const Node: TAbstractLightNode);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    { Determines the headlight look, if we use a headlight
      (which is determined by the algorithm described at @link(UseHeadlight) and
      @link(TUseHeadlight)).
      By default it's a simplest directional headlight,
      but you can customize it, and thus you can use a point light
      or a spot light for a headlight.
      Just like https://castle-engine.io/x3d_implementation_navigation_extensions.php#section_ext_headlight .

      This is never @nil.
      Assigning here @nil simply causes us to recreate it using
      the simplest directional headlight. }
    property HeadlightNode: TAbstractLightNode
      read GetHeadlightNode write SetHeadlightNode;

    { Headlight used to light the scene.

      Returns non-nil headlight node
      if the algorithm described at @link(TCastleViewport.UseHeadlight) and
      @link(TUseHeadlight) indicates we should use a headlight.
      Otherwise returns @nil, to indicate we do not show a headlight now. }
    function InternalHeadlight: TAbstractLightNode;
  published
    { The main scene of the world. It's not necessary to set this.
      It adds some optional features that require a notion of
      the "main" scene to make sense.

      The scene you set here @italic(must) also be added to our @link(Items).

      The MainScene is used for a couple of things:

      @unorderedList(
        @item(Determines initial @link(Camera) (if @link(AutoCamera))
          and @link(Navigation) (if @link(AutoNavigation)) properties.
          This includes camera position, orientation, projection.
          This includes navigation type (examine, walk, fly), move speed.
          These follow the X3D Viewpoint, OrthoViewpoint
          and NavigationInfo nodes defined inside the MainScene.

          Later changes to nodes Viewpoint/NavigatioInfo using X3D events inside
          MainScene may also influence the @link(Camera) and @link(Navigation).
          For example in X3D you can animate the Viewpoint position,
          and it will actually animate our @link(Camera) position.

          If both @link(AutoCamera) and @link(AutoNavigation) are @false,
          none of these things are applied.
        )

        @item(Determines what background is rendered.
          If the MainScene contains an X3D Background node (or other
          node descending from TAbstractBackgroundNode),
          it will be used.

          Otherwise we render a background using @link(BackgroundColor).

          Note that when @link(Transparent) is @true,
          we never render any background (neither from MainScene,
          nor from @link(BackgroundColor)).
        )

        @item(Determines whether headlight is used if @link(UseHeadlight)
          is hlMainScene. The value of
          @link(TCastleSceneCore.HeadlightOn MainScene.HeadlightOn)
          then determines the headlight.
          The initial
          @link(TCastleSceneCore.HeadlightOn MainScene.HeadlightOn)
          value depends on the X3D NavigationInfo node inside MainScene.)

        @item(Determines the main light casting shadow volumes.)

        @item(Determines lights shining on all scenes, if @link(UseGlobalLights).)

        @item(Determines fog on all scenes, if @link(UseGlobalFog).)

        @link(The screen effects defined inside MainScene (TScreenEffectNode)
          are automatically used.)

        @link(PointingDeviceMove and PointingDeviceActivate always pass events to the MainScene,
          even if mouse cursor is not pointing at the MainScene.
          This way MainScene reliably knows when you move mouse such that it
          @italic(no longer) points at the MainScene.)
      )

      Freeing MainScene will automatically set this property to @nil. }
    property MainScene: TCastleScene read FMainScene write SetMainScene;

    { Whether the headlight is shown, see @link(TUseHeadlight) for possible values. }
    property UseHeadlight: TUseHeadlight
      read FUseHeadlight write FUseHeadlight default hlMainScene;
  end;

{$endif read_interface}

{$ifdef read_implementation}

{ TCastleRootTransform.TFreeNotificationProxy -------------------------------- }

procedure TCastleRootTransform.TFreeNotificationProxy.Notification(
  AComponent: TComponent; Operation: TOperation);
var
  O: TCastleRootTransform;
begin
  inherited;
  O := Owner as TCastleRootTransform;
  if (Operation = opRemove) and (AComponent = O.FMainScene) then
    O.MainScene := nil;
end;

{ TCastleRootTransform ------------------------------------------------------- }

constructor TCastleRootTransform.Create(AOwner: TComponent);
begin
  inherited;
  MainSceneFreeNotificationProxy := TFreeNotificationProxy.Create(Self);
  FUseHeadlight := hlMainScene;
end;

destructor TCastleRootTransform.Destroy;
begin
  { unregister self from MainScene callbacs,
    make MainScene.RemoveFreeNotification(Self)... this is all
    done by SetMainScene(nil) already. }
  MainScene := nil;

  FreeIfUnusedAndNil(FHeadlightNode);
  inherited;
end;

procedure TCastleRootTransform.SetMainScene(const Value: TCastleScene);
begin
  if FMainScene <> Value then
  begin
    if FMainScene <> nil then
    begin
      FMainScene.RemoveFreeNotification(MainSceneFreeNotificationProxy);
      FMainScene.OnBoundViewpointVectorsChanged := nil;
      FMainScene.OnBoundNavigationInfoFieldsChanged := nil;
      { Check FMainScene.*Stack <> nil,
        because this may happen from MainScene destruction notification,
        when *Stack is already freed. }
      if FMainScene.ViewpointStack <> nil then
        FMainScene.ViewpointStack.OnBoundChanged := nil;
      if FMainScene.NavigationInfoStack <> nil then
        FMainScene.NavigationInfoStack.OnBoundChanged := nil;
    end;

    FMainScene := Value;

    if FMainScene <> nil then
    begin
      FMainScene.FreeNotification(MainSceneFreeNotificationProxy);
      FMainScene.OnBoundViewpointVectorsChanged := @MainScene_BoundViewpointVectorsChanged;
      FMainScene.OnBoundNavigationInfoFieldsChanged := @MainScene_BoundNavigationInfoChanged;
      FMainScene.ViewpointStack.OnBoundChanged := @MainScene_BoundViewpointChanged;
      FMainScene.NavigationInfoStack.OnBoundChanged := @MainScene_BoundNavigationInfoChanged;
    end;

    { Setting MainScene may change lights, if MainScene determines the headlight
      when UseHeadlight = hlMainScene.
      So we use vcVisibleNonGeometry.
    }
    VisibleChangeHere([vcVisibleNonGeometry]);
  end;
end;

procedure TCastleRootTransform.MainScene_BoundViewpointChanged(Sender: TObject);
begin
  if (MainCamera <> nil) and
     Assigned(MainCamera.InternalOnSceneBoundViewpointChanged) then
              MainCamera.InternalOnSceneBoundViewpointChanged(Sender);
end;

procedure TCastleRootTransform.MainScene_BoundViewpointVectorsChanged(Sender: TObject);
begin
  if (MainCamera <> nil) and
     Assigned(MainCamera.InternalOnSceneBoundViewpointVectorsChanged) then
              MainCamera.InternalOnSceneBoundViewpointVectorsChanged(Sender);
end;

procedure TCastleRootTransform.MainScene_BoundNavigationInfoChanged(Sender: TObject);
begin
  if (MainCamera <> nil) and
     Assigned(MainCamera.InternalOnSceneBoundNavigationInfoChanged) then
              MainCamera.InternalOnSceneBoundNavigationInfoChanged(Sender);
end;

function TCastleRootTransform.GetHeadlightNode: TAbstractLightNode;
begin
  { HeadlightNode is never nil, so recreate it now if nil. }

  if FHeadlightNode = nil then
    { Nothing more needed, all DirectionalLight default properties
      are suitable for default headlight. }
    FHeadlightNode := TDirectionalLightNode.Create;

  Result := FHeadlightNode;
end;

procedure TCastleRootTransform.SetHeadlightNode(const Node: TAbstractLightNode);
begin
  if FHeadlightNode <> Node then
  begin
    FreeIfUnusedAndNil(FHeadlightNode);
    FHeadlightNode := Node;
  end;
end;

function TCastleRootTransform.InternalHeadlight: TAbstractLightNode;
begin
  Result := nil;

  case UseHeadlight of
    hlOn : Result := HeadlightNode;
    hlOff: Result := nil;
    hlMainScene:
      if (MainScene <> nil) and MainScene.HeadlightOn then
      begin
        Result := MainScene.CustomHeadlight;
        if Result = nil then
          Result := HeadlightNode;
        Assert(Result <> nil);
      end;
    {$ifndef COMPILER_CASE_ANALYSIS}
    else raise EInternalError.Create(2018081902);
    {$endif}
  end;
end;

{$endif read_implementation}
