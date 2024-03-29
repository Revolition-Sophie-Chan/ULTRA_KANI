xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 38;
 0.00000;2.39200;0.00000;,
 0.00000;2.39200;-130.68420;,
 76.51830;2.39200;4.06710;,
 0.00000;2.39200;73.30820;,
 -112.15520;2.39200;36.46070;,
 52.02680;74.18790;2.76530;,
 76.51830;2.39200;4.06710;,
 0.00000;2.39200;-130.68420;,
 0.00000;49.97000;-69.00480;,
 0.00000;102.34840;-39.91140;,
 45.44670;93.47720;2.41560;,
 0.00000;60.13630;54.43640;,
 0.00000;2.39200;73.30820;,
 52.02680;74.18790;2.76530;,
 45.44670;93.47720;2.41560;,
 0.00000;99.74080;41.49310;,
 -76.56290;43.13130;29.83870;,
 -112.15520;2.39200;36.46070;,
 0.00000;60.13630;54.43640;,
 0.00000;99.74080;41.49310;,
 -48.95220;109.48510;19.05320;,
 0.00000;49.97000;-69.00480;,
 0.00000;2.39200;-130.68420;,
 -76.56290;43.13130;29.83870;,
 -48.95220;109.48510;19.05320;,
 0.00000;102.34840;-39.91140;,
 13.07210;125.64640;-21.05330;,
 23.24140;141.37000;-0.40820;,
 35.24920;126.84380;1.03020;,
 35.24920;126.84380;1.03020;,
 23.24140;141.37000;-0.40820;,
 18.15240;133.80400;14.26830;,
 18.15240;133.80400;14.26830;,
 23.24140;141.37000;-0.40820;,
 -3.62570;136.36090;6.91060;,
 -3.62570;136.36090;6.91060;,
 23.24140;141.37000;-0.40820;,
 13.07210;125.64640;-21.05330;;
 
 20;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,1;,
 4;5,6,7,8;,
 4;5,8,9,10;,
 4;11,12,6,13;,
 4;11,13,14,15;,
 4;16,17,12,18;,
 4;16,18,19,20;,
 4;21,22,17,23;,
 4;21,23,24,25;,
 3;26,27,28;,
 4;26,28,10,9;,
 3;29,30,31;,
 4;29,31,15,14;,
 3;32,33,34;,
 4;32,34,20,19;,
 3;35,36,37;,
 4;35,37,25,24;;
 
 MeshMaterialList {
  1;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  25;
  0.000000;-1.000000;0.000000;,
  0.618750;0.447546;-0.645640;,
  0.701359;0.242181;-0.670405;,
  0.417193;0.420371;0.805753;,
  -0.273479;0.490222;0.827582;,
  0.732682;0.350611;-0.583309;,
  0.183422;0.319315;0.929728;,
  -0.335100;0.316751;0.887342;,
  0.660403;0.317634;-0.680424;,
  0.299272;0.668556;0.680786;,
  -0.116352;0.794742;0.595691;,
  0.750858;0.397476;-0.527470;,
  0.191494;0.332703;0.923385;,
  0.652094;0.235513;0.720629;,
  0.652094;0.235512;0.720629;,
  0.652336;0.232469;0.721398;,
  -0.319413;0.342488;0.883560;,
  -0.350478;0.290722;0.890307;,
  -0.727488;0.413063;-0.547851;,
  -0.682687;0.554562;-0.475814;,
  -0.654500;0.477553;-0.586150;,
  0.656834;0.410818;0.632295;,
  0.317823;0.793363;0.519196;,
  -0.406960;0.753911;-0.515754;,
  -0.286516;0.824966;-0.487174;;
  20;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;5,11,11,5;,
  4;5,5,2,2;,
  4;6,12,13,14;,
  4;6,14,15,3;,
  4;7,16,12,6;,
  4;7,6,17,4;,
  4;18,19,19,18;,
  4;18,18,20,20;,
  3;8,1,8;,
  4;8,8,2,2;,
  3;21,22,9;,
  4;21,9,3,15;,
  3;9,22,10;,
  4;9,10,4,3;,
  3;23,24,23;,
  4;23,23,20,20;;
 }
 MeshTextureCoords {
  38;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.209990;0.679930;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.037640;0.698870;,
  0.055700;0.554380;,
  0.199240;0.593930;,
  0.435640;0.742570;,
  0.500000;1.000000;,
  0.250000;0.679930;,
  0.250000;0.593930;,
  0.391500;0.566010;,
  0.681890;0.818380;,
  0.750000;1.000000;,
  0.467820;0.742570;,
  0.445750;0.566010;,
  0.570960;0.522570;,
  0.849430;0.698870;,
  1.000000;1.000000;,
  0.704600;0.818380;,
  0.630640;0.522570;,
  0.777190;0.554380;,
  0.088450;0.292440;,
  0.125000;0.000000;,
  0.156660;0.253300;,
  0.250000;0.253300;,
  0.250000;0.000000;,
  0.298660;0.194640;,
  0.399330;0.194640;,
  0.375000;0.000000;,
  0.446080;0.189530;,
  0.547380;0.189530;,
  0.500000;0.000000;,
  0.646220;0.292440;;
 }
}
