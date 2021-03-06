{
  Copyright 2002-2018 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Inventor nodes that didn't make it into any VRML version. } { }

{$ifdef read_interface}
  { IndexedTriangleMesh (from Inventor 1.0). }
  TIndexedTriangleMeshNode_1 = class(TIndexedFacesOrTrianglesNode_1)
    class function ClassX3DType: string; override;

    procedure InternalCoordPolygons(
      State: TX3DGraphTraverseState;
      PolygonHandler: TIndexedPolygonHandler); override;

    function InternalTexCoord(State: TX3DGraphTraverseState;
      out ATexCoord: TX3DNode): boolean; override;
  end;

  { RotationXYZ node (from Inventor). It's not in VRML 1.0 spec.
    But some invalid VRML 1.0 models use it,
    e.g. [http://www-vrl.umich.edu/sel_prj/EECS498/]. }
  TRotationXYZNode = class(TAbstractTransformationNode_1)
    procedure CreateNode; override;
    class function ClassX3DType: string; override;

    strict private FFdAxis: TSFEnum;
    public property FdAxis: TSFEnum read FFdAxis;

    strict private FFdAngle: TSFFloat;
    public property FdAngle: TSFFloat read FFdAngle;

    procedure Transformation(out Matrix, InvertedMatrix: TMatrix4); override;
    function TransformScale: Single; override;
  end;
{$endif read_interface}

{$ifdef read_implementation}
class function TIndexedTriangleMeshNode_1.ClassX3DType: string;
begin
  result := 'IndexedTriangleMesh';
end;

function TIndexedTriangleMeshNode_1.InternalTexCoord(State: TX3DGraphTraverseState;
  out ATexCoord: TX3DNode): boolean;
begin
  Result := true;
  ATexCoord := State.VRML1State.TextureCoordinate2;
end;

procedure TRotationXYZNode.CreateNode;
begin
  inherited;

  FFdAxis := TSFEnum.Create(Self, true, 'axis' , ['X', 'Y', 'Z'], 0);
   FdAxis.ChangesAlways := [chEverything];
  AddField(FFdAxis);

  FFdAngle := TSFFloat.Create(Self, true, 'angle', 0);
   FdAngle.ChangesAlways := [chEverything];
  AddField(FFdAngle);
end;

class function TRotationXYZNode.ClassX3DType: string;
begin
  Result := 'RotationXYZ';
end;

procedure TRotationXYZNode.Transformation(
  out Matrix, InvertedMatrix: TMatrix4);
begin
  RotationMatricesRad(FdAngle.Value, TVector3.One[FdAxis.Value],
    Matrix, InvertedMatrix);
end;

function TRotationXYZNode.TransformScale: Single;
begin
  Result := 1;
end;

procedure RegistedInventorNodes;
begin
  NodesManager.RegisterNodeClasses([
    TIndexedTriangleMeshNode_1,
    TRotationXYZNode
  ]);
end;
{$endif read_implementation}
