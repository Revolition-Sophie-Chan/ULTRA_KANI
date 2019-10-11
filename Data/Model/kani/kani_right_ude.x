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
 104;
 7.45934;31.54773;14.53226;,
 7.94988;30.55831;15.26243;,
 7.62789;30.45770;16.54262;,
 6.64681;32.43653;15.08229;,
 8.76241;29.66951;14.71239;,
 9.25294;28.68010;15.44256;,
 9.08440;29.77012;13.43220;,
 9.89692;28.88132;12.88216;,
 8.59386;30.75954;12.70203;,
 8.91585;30.86015;11.42184;,
 7.78133;31.64834;13.25207;,
 7.29079;32.63775;12.52190;,
 7.30590;30.35709;17.82282;,
 5.83429;33.32533;15.63233;,
 9.74348;27.69069;16.17272;,
 10.70945;27.99252;12.33213;,
 9.23784;30.96076;10.14164;,
 6.80026;33.62716;11.79174;,
 6.98391;30.25648;19.10302;,
 5.02176;34.21413;16.18236;,
 10.23402;26.70127;16.90289;,
 11.52198;27.10372;11.78210;,
 9.55983;31.06137;8.86144;,
 6.30972;34.61658;11.06157;,
 6.66192;30.15587;20.38321;,
 4.20923;35.10293;16.73239;,
 10.72456;25.71186;17.63305;,
 12.33450;26.21492;11.23207;,
 9.88182;31.16198;7.58125;,
 5.81918;35.60599;10.33141;,
 4.20923;35.10293;16.73239;,
 6.66192;30.15587;20.38321;,
 13.34778;34.99210;22.44490;,
 10.89509;39.93917;18.79407;,
 10.72456;25.71186;17.63305;,
 17.41042;30.54809;19.69473;,
 12.33450;26.21492;11.23207;,
 19.02036;31.05115;13.29375;,
 9.88182;31.16198;7.58125;,
 16.56768;35.99821;9.64293;,
 5.81918;35.60599;10.33141;,
 12.50504;40.44222;12.39309;,
 4.20923;35.10293;16.73239;,
 10.89509;39.93917;18.79407;,
 20.03364;39.82833;24.50658;,
 17.58096;44.77540;20.85575;,
 24.09628;35.38433;21.75641;,
 25.70623;35.88738;15.35543;,
 23.25354;40.83445;11.70461;,
 19.19090;45.27845;14.45477;,
 17.58096;44.77540;20.85575;,
 26.71950;44.66457;26.56826;,
 24.26682;49.61163;22.91744;,
 30.78214;40.22056;23.81809;,
 32.39209;40.72362;17.41711;,
 29.93940;45.67068;13.76629;,
 25.87676;50.11469;16.51645;,
 24.26682;49.61163;22.91744;,
 33.40536;49.50080;28.62994;,
 30.95268;54.44786;24.97912;,
 37.46800;45.05679;25.87978;,
 39.07795;45.55985;19.47879;,
 36.62526;50.50691;15.82797;,
 32.56263;54.95092;18.57813;,
 30.95268;54.44786;24.97912;,
 40.09122;54.33703;30.69162;,
 37.63854;59.28410;27.04080;,
 44.15386;49.89302;27.94146;,
 45.76381;50.39608;21.54047;,
 43.31112;55.34314;17.88965;,
 39.24849;59.78715;20.63982;,
 37.63854;59.28410;27.04080;,
 37.63854;59.28410;27.04080;,
 40.09122;54.33703;30.69162;,
 40.41321;54.43764;29.41142;,
 38.45107;58.39529;26.49077;,
 44.15386;49.89302;27.94146;,
 43.66332;50.88244;27.21129;,
 45.76381;50.39608;21.54047;,
 44.95128;51.28488;22.09050;,
 43.31112;55.34314;17.88965;,
 42.98913;55.24253;19.16985;,
 39.24849;59.78715;20.63982;,
 39.73902;58.79774;21.36998;,
 40.73520;54.53825;28.13123;,
 39.26359;57.50649;25.94073;,
 43.17279;51.87185;26.48113;,
 44.13875;52.17368;22.64054;,
 42.66714;55.14192;20.45004;,
 40.22956;57.80833;22.10014;,
 41.05719;54.63887;26.85103;,
 40.07612;56.61769;25.39070;,
 42.68225;52.86126;25.75096;,
 43.32623;53.06248;23.19057;,
 42.34515;55.04131;21.73024;,
 40.72010;56.81891;22.83031;,
 41.37918;54.73948;25.57083;,
 40.88865;55.72889;24.84067;,
 42.19171;53.85067;25.02080;,
 42.51370;53.95129;23.74060;,
 42.02316;54.94070;23.01044;,
 41.21064;55.82950;23.56047;,
 8.27187;30.65893;13.98223;,
 41.70117;54.84009;24.29064;;
 
 90;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,0,3,11;,
 4;3,2,12,13;,
 4;2,5,14,12;,
 4;5,7,15,14;,
 4;7,9,16,15;,
 4;9,11,17,16;,
 4;11,3,13,17;,
 4;13,12,18,19;,
 4;12,14,20,18;,
 4;14,15,21,20;,
 4;15,16,22,21;,
 4;16,17,23,22;,
 4;17,13,19,23;,
 4;19,18,24,25;,
 4;18,20,26,24;,
 4;20,21,27,26;,
 4;21,22,28,27;,
 4;22,23,29,28;,
 4;23,19,25,29;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;33,32,44,45;,
 4;32,35,46,44;,
 4;35,37,47,46;,
 4;37,39,48,47;,
 4;39,41,49,48;,
 4;41,43,50,49;,
 4;45,44,51,52;,
 4;44,46,53,51;,
 4;46,47,54,53;,
 4;47,48,55,54;,
 4;48,49,56,55;,
 4;49,50,57,56;,
 4;52,51,58,59;,
 4;51,53,60,58;,
 4;53,54,61,60;,
 4;54,55,62,61;,
 4;55,56,63,62;,
 4;56,57,64,63;,
 4;59,58,65,66;,
 4;58,60,67,65;,
 4;60,61,68,67;,
 4;61,62,69,68;,
 4;62,63,70,69;,
 4;63,64,71,70;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,72,75,83;,
 4;75,74,84,85;,
 4;74,77,86,84;,
 4;77,79,87,86;,
 4;79,81,88,87;,
 4;81,83,89,88;,
 4;83,75,85,89;,
 4;85,84,90,91;,
 4;84,86,92,90;,
 4;86,87,93,92;,
 4;87,88,94,93;,
 4;88,89,95,94;,
 4;89,85,91,95;,
 4;91,90,96,97;,
 4;90,92,98,96;,
 4;92,93,99,98;,
 4;93,94,100,99;,
 4;94,95,101,100;,
 4;95,91,97,101;,
 3;1,0,102;,
 3;4,1,102;,
 3;6,4,102;,
 3;8,6,102;,
 3;10,8,102;,
 3;0,10,102;,
 3;97,96,103;,
 3;96,98,103;,
 3;98,99,103;,
 3;99,100,103;,
 3;100,101,103;,
 3;101,97,103;;
 
 MeshMaterialList {
  1;
  90;
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
   0.401569;0.015686;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\Model\\kani\\kani_texture.jpg";
   }
  }
 }
 MeshNormals {
  98;
  -0.786079;-0.568614;-0.242400;,
  -0.786079;-0.568613;-0.242402;,
  -0.786081;-0.568611;-0.242401;,
  -0.786082;-0.568611;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786079;-0.568615;-0.242399;,
  -0.786081;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786081;-0.568612;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786081;-0.568612;-0.242399;,
  -0.786081;-0.568613;-0.242398;,
  -0.786080;-0.568614;-0.242398;,
  -0.786080;-0.568613;-0.242400;,
  -0.786080;-0.568613;-0.242400;,
  -0.786080;-0.568612;-0.242400;,
  -0.786079;-0.568614;-0.242400;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568614;-0.242399;,
  -0.786078;-0.568615;-0.242400;,
  -0.786079;-0.568614;-0.242400;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242399;,
  -0.786080;-0.568613;-0.242398;,
  -0.786079;-0.568614;-0.242399;,
  -0.494762;0.343729;0.798161;,
  0.073504;-0.475359;0.876716;,
  0.568265;-0.819087;0.078555;,
  0.494762;-0.343729;-0.798161;,
  -0.073503;0.475358;-0.876717;,
  -0.494762;0.343729;0.798161;,
  0.073504;-0.475359;0.876716;,
  0.568265;-0.819087;0.078556;,
  0.494761;-0.343729;-0.798162;,
  -0.073503;0.475358;-0.876717;,
  -0.494762;0.343729;0.798161;,
  0.073504;-0.475359;0.876716;,
  0.568265;-0.819087;0.078556;,
  0.494761;-0.343729;-0.798162;,
  -0.073503;0.475358;-0.876717;,
  -0.494762;0.343729;0.798161;,
  0.073503;-0.475358;0.876716;,
  0.568265;-0.819088;0.078555;,
  0.494761;-0.343729;-0.798162;,
  -0.073503;0.475358;-0.876716;,
  -0.494762;0.343729;0.798161;,
  0.073503;-0.475358;0.876717;,
  0.568265;-0.819088;0.078555;,
  0.494761;-0.343729;-0.798162;,
  -0.073503;0.475359;-0.876716;,
  0.786082;0.568611;0.242399;,
  0.786081;0.568612;0.242400;,
  0.786080;0.568613;0.242400;,
  0.786080;0.568613;0.242399;,
  0.786080;0.568613;0.242399;,
  0.786081;0.568611;0.242399;,
  0.786080;0.568612;0.242400;,
  0.786080;0.568613;0.242400;,
  0.786080;0.568613;0.242400;,
  0.786080;0.568613;0.242398;,
  0.786080;0.568613;0.242398;,
  0.786081;0.568612;0.242399;,
  0.786079;0.568614;0.242400;,
  0.786080;0.568613;0.242400;,
  0.786080;0.568613;0.242399;,
  0.786080;0.568613;0.242399;,
  0.786080;0.568613;0.242398;,
  0.786080;0.568614;0.242398;,
  0.786081;0.568611;0.242399;,
  0.786081;0.568612;0.242399;,
  0.786080;0.568613;0.242400;,
  0.786079;0.568614;0.242400;,
  0.786080;0.568613;0.242399;,
  0.786081;0.568611;0.242399;,
  -0.786080;-0.568613;-0.242400;,
  0.786081;0.568612;0.242400;,
  -0.494762;0.343729;0.798161;,
  0.073503;-0.475359;0.876716;,
  0.568265;-0.819087;0.078554;,
  0.494762;-0.343729;-0.798161;,
  -0.073503;0.475358;-0.876717;,
  -0.568265;0.819087;-0.078555;,
  -0.568265;0.819087;-0.078556;,
  -0.568265;0.819087;-0.078555;,
  -0.568265;0.819087;-0.078555;,
  -0.568265;0.819088;-0.078555;,
  -0.568265;0.819087;-0.078555;,
  0.786081;0.568611;0.242399;,
  0.786080;0.568612;0.242400;,
  0.786079;0.568614;0.242400;,
  0.786079;0.568614;0.242399;,
  0.786080;0.568613;0.242399;,
  0.786081;0.568612;0.242399;;
  90;
  4;0,1,7,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,0,6,11;,
  4;6,7,13,12;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,6,12,17;,
  4;12,13,19,18;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,12,18,23;,
  4;18,19,25,24;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,18,24,29;,
  4;81,81,30,30;,
  4;82,82,31,31;,
  4;83,83,32,32;,
  4;84,84,33,33;,
  4;85,85,34,34;,
  4;86,86,87,87;,
  4;30,30,35,35;,
  4;31,31,36,36;,
  4;32,32,37,37;,
  4;33,33,38,38;,
  4;34,34,39,39;,
  4;87,87,88,88;,
  4;35,35,40,40;,
  4;36,36,41,41;,
  4;37,37,42,42;,
  4;38,38,43,43;,
  4;39,39,44,44;,
  4;88,88,89,89;,
  4;40,40,45,45;,
  4;41,41,46,46;,
  4;42,42,47,47;,
  4;43,43,48,48;,
  4;44,44,49,49;,
  4;89,89,90,90;,
  4;45,45,50,50;,
  4;46,46,51,51;,
  4;47,47,52,52;,
  4;48,48,53,53;,
  4;49,49,54,54;,
  4;90,90,91,91;,
  4;92,93,56,55;,
  4;93,94,57,56;,
  4;94,95,58,57;,
  4;95,96,59,58;,
  4;96,97,60,59;,
  4;97,92,55,60;,
  4;55,56,62,61;,
  4;56,57,63,62;,
  4;57,58,64,63;,
  4;58,59,65,64;,
  4;59,60,66,65;,
  4;60,55,61,66;,
  4;61,62,68,67;,
  4;62,63,69,68;,
  4;63,64,70,69;,
  4;64,65,71,70;,
  4;65,66,72,71;,
  4;66,61,67,72;,
  4;67,68,74,73;,
  4;68,69,75,74;,
  4;69,70,76,75;,
  4;70,71,77,76;,
  4;71,72,78,77;,
  4;72,67,73,78;,
  3;1,0,79;,
  3;2,1,79;,
  3;3,2,79;,
  3;4,3,79;,
  3;5,4,79;,
  3;0,5,79;,
  3;73,74,80;,
  3;74,75,80;,
  3;75,76,80;,
  3;76,77,80;,
  3;77,78,80;,
  3;78,73,80;;
 }
 MeshTextureCoords {
  104;
  0.515625;0.129187;,
  0.484375;0.129187;,
  0.468750;0.102123;,
  0.531250;0.102123;,
  0.468750;0.156250;,
  0.437500;0.156250;,
  0.484375;0.183313;,
  0.468750;0.210377;,
  0.515625;0.183313;,
  0.531250;0.210377;,
  0.531250;0.156250;,
  0.562500;0.156250;,
  0.453125;0.075060;,
  0.546875;0.075060;,
  0.406250;0.156250;,
  0.453125;0.237440;,
  0.546875;0.237440;,
  0.593750;0.156250;,
  0.437500;0.047997;,
  0.562500;0.047997;,
  0.375000;0.156250;,
  0.437500;0.264503;,
  0.562500;0.264503;,
  0.625000;0.156250;,
  0.421875;0.020934;,
  0.578125;0.020934;,
  0.343750;0.156250;,
  0.421875;0.291566;,
  0.578125;0.291566;,
  0.656250;0.156250;,
  0.375000;0.312500;,
  0.416667;0.312500;,
  0.416667;0.387688;,
  0.375000;0.387688;,
  0.458333;0.312500;,
  0.458333;0.387688;,
  0.500000;0.312500;,
  0.500000;0.387688;,
  0.541667;0.312500;,
  0.541667;0.387688;,
  0.583333;0.312500;,
  0.583333;0.387688;,
  0.625000;0.312500;,
  0.625000;0.387688;,
  0.416667;0.462876;,
  0.375000;0.462876;,
  0.458333;0.462876;,
  0.500000;0.462876;,
  0.541667;0.462876;,
  0.583333;0.462876;,
  0.625000;0.462876;,
  0.416667;0.538064;,
  0.375000;0.538064;,
  0.458333;0.538064;,
  0.500000;0.538064;,
  0.541667;0.538064;,
  0.583333;0.538064;,
  0.625000;0.538064;,
  0.416667;0.613252;,
  0.375000;0.613252;,
  0.458333;0.613252;,
  0.500000;0.613252;,
  0.541667;0.613252;,
  0.583333;0.613252;,
  0.625000;0.613252;,
  0.416667;0.688440;,
  0.375000;0.688440;,
  0.458333;0.688440;,
  0.500000;0.688440;,
  0.541667;0.688440;,
  0.583333;0.688440;,
  0.625000;0.688440;,
  0.578125;0.979066;,
  0.421875;0.979066;,
  0.437500;0.952003;,
  0.562500;0.952003;,
  0.343750;0.843750;,
  0.375000;0.843750;,
  0.421875;0.708434;,
  0.437500;0.735497;,
  0.578125;0.708434;,
  0.562500;0.735497;,
  0.656250;0.843750;,
  0.625000;0.843750;,
  0.453125;0.924940;,
  0.546875;0.924940;,
  0.406250;0.843750;,
  0.453125;0.762560;,
  0.546875;0.762560;,
  0.593750;0.843750;,
  0.468750;0.897877;,
  0.531250;0.897877;,
  0.437500;0.843750;,
  0.468750;0.789623;,
  0.531250;0.789623;,
  0.562500;0.843750;,
  0.484375;0.870813;,
  0.515625;0.870813;,
  0.468750;0.843750;,
  0.484375;0.816687;,
  0.515625;0.816687;,
  0.531250;0.843750;,
  0.500000;0.150000;,
  0.500000;0.837500;;
 }
}
