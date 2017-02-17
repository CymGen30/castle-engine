{ -*- buffer-read-only: t -*-

  Copyright 2015-2017 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Automatically generated node properties.

  Do not edit this file manually!
  To add new properties, add them to text files in nodes_specification/components/ ,
  and regenerate include files by running
  nodes_specification/generate_x3d_nodes_to_pascal.lpr .

  The documentation for properties should go to x3dnodes_documentation.txt . }

{$ifdef read_interface}

  private
    function GetYScale: Single;
    procedure SetYScale(const Value: Single);
    function GetCcw: boolean;
    procedure SetCcw(const Value: boolean);
    function GetColorPerVertex: boolean;
    procedure SetColorPerVertex(const Value: boolean);
    function GetCreaseAngle: Double;
    procedure SetCreaseAngle(const Value: Double);
    function GetGeoGridOrigin: TVector3Double;
    procedure SetGeoGridOrigin(const Value: TVector3Double);
    function GetNormalPerVertex: boolean;
    procedure SetNormalPerVertex(const Value: boolean);
    function GetXDimension: Integer;
    procedure SetXDimension(const Value: Integer);
    function GetXSpacing: Double;
    procedure SetXSpacing(const Value: Double);
    function GetZDimension: Integer;
    procedure SetZDimension(const Value: Integer);
    function GetZSpacing: Double;
    procedure SetZSpacing(const Value: Double);
  public
    property YScale: Single read GetYScale write SetYScale;
    property Ccw: boolean read GetCcw write SetCcw;
    property ColorPerVertex: boolean read GetColorPerVertex write SetColorPerVertex;
    property CreaseAngle: Double read GetCreaseAngle write SetCreaseAngle;
    property GeoGridOrigin: TVector3Double read GetGeoGridOrigin write SetGeoGridOrigin;
    property NormalPerVertex: boolean read GetNormalPerVertex write SetNormalPerVertex;
    property XDimension: Integer read GetXDimension write SetXDimension;
    property XSpacing: Double read GetXSpacing write SetXSpacing;
    property ZDimension: Integer read GetZDimension write SetZDimension;
    property ZSpacing: Double read GetZSpacing write SetZSpacing;

{$endif read_interface}

{$ifdef read_implementation}

{ TGeoElevationGridNode ----------------------------------------------- }

function TGeoElevationGridNode.GetYScale: Single;
begin
  Result := FdYScale.Value;
end;

procedure TGeoElevationGridNode.SetYScale(const Value: Single);
begin
  FdYScale.Send(Value);
end;

function TGeoElevationGridNode.GetCcw: boolean;
begin
  Result := FdCcw.Value;
end;

procedure TGeoElevationGridNode.SetCcw(const Value: boolean);
begin
  FdCcw.Send(Value);
end;

function TGeoElevationGridNode.GetColorPerVertex: boolean;
begin
  Result := FdColorPerVertex.Value;
end;

procedure TGeoElevationGridNode.SetColorPerVertex(const Value: boolean);
begin
  FdColorPerVertex.Send(Value);
end;

function TGeoElevationGridNode.GetCreaseAngle: Double;
begin
  Result := FdCreaseAngle.Value;
end;

procedure TGeoElevationGridNode.SetCreaseAngle(const Value: Double);
begin
  FdCreaseAngle.Send(Value);
end;

function TGeoElevationGridNode.GetGeoGridOrigin: TVector3Double;
begin
  Result := FdGeoGridOrigin.Value;
end;

procedure TGeoElevationGridNode.SetGeoGridOrigin(const Value: TVector3Double);
begin
  FdGeoGridOrigin.Send(Value);
end;

function TGeoElevationGridNode.GetNormalPerVertex: boolean;
begin
  Result := FdNormalPerVertex.Value;
end;

procedure TGeoElevationGridNode.SetNormalPerVertex(const Value: boolean);
begin
  FdNormalPerVertex.Send(Value);
end;

function TGeoElevationGridNode.GetXDimension: Integer;
begin
  Result := FdXDimension.Value;
end;

procedure TGeoElevationGridNode.SetXDimension(const Value: Integer);
begin
  FdXDimension.Send(Value);
end;

function TGeoElevationGridNode.GetXSpacing: Double;
begin
  Result := FdXSpacing.Value;
end;

procedure TGeoElevationGridNode.SetXSpacing(const Value: Double);
begin
  FdXSpacing.Send(Value);
end;

function TGeoElevationGridNode.GetZDimension: Integer;
begin
  Result := FdZDimension.Value;
end;

procedure TGeoElevationGridNode.SetZDimension(const Value: Integer);
begin
  FdZDimension.Send(Value);
end;

function TGeoElevationGridNode.GetZSpacing: Double;
begin
  Result := FdZSpacing.Value;
end;

procedure TGeoElevationGridNode.SetZSpacing(const Value: Double);
begin
  FdZSpacing.Send(Value);
end;

{$endif read_implementation}