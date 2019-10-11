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
 114;
 5.48847;5.48832;6.03465;,
 5.29957;4.88409;6.99630;,
 5.61236;6.31933;8.20687;,
 5.96140;7.43579;6.42993;,
 5.57818;4.04022;7.72832;,
 6.12715;4.76005;9.55946;,
 -0.28757;-1.01238;7.06664;,
 1.88256;-0.55397;11.00590;,
 3.30136;-2.24797;4.55485;,
 8.51402;-2.83705;6.36471;,
 4.71064;-1.51188;2.05491;,
 11.11804;-1.47695;1.74545;,
 3.11473;0.76469;1.03127;,
 8.16920;2.72962;-0.14601;,
 -0.55149;3.24817;2.08355;,
 1.39491;7.31850;1.79835;,
 5.48847;5.48832;6.03465;,
 5.96140;7.43579;6.42993;,
 6.64095;8.17999;9.74327;,
 7.09699;9.63872;7.42159;,
 7.31355;6.14271;11.51050;,
 5.03772;1.62819;15.15159;,
 13.70215;-1.35481;9.08759;,
 17.10446;0.42227;3.05222;,
 13.25163;5.91842;0.58093;,
 4.40058;11.91408;3.12135;,
 7.09699;9.63872;7.42159;,
 8.22877;10.18282;11.37160;,
 8.72238;11.76174;8.85863;,
 8.95679;7.97767;13.28444;,
 8.69757;5.20189;18.87257;,
 18.07587;1.97312;12.30895;,
 21.75850;3.89662;5.77631;,
 17.58822;9.84559;3.10139;,
 8.00792;16.33525;5.85114;,
 8.72238;11.76174;8.85863;,
 10.13407;12.02289;12.84396;,
 10.59012;13.48163;10.52229;,
 10.80668;9.98560;14.61119;,
 12.30491;9.62306;21.60234;,
 20.96934;6.64007;15.53836;,
 24.37164;8.41714;9.50299;,
 20.51882;13.91330;7.03168;,
 11.66778;19.90896;9.57211;,
 10.59012;13.48163;10.52229;,
 11.08832;29.08921;27.70761;,
 10.93444;29.28505;22.23895;,
 11.27926;23.71837;28.74966;,
 15.31058;14.21863;22.92534;,
 21.94205;11.93555;18.28416;,
 24.54605;13.29566;13.66490;,
 21.59722;17.50223;11.77345;,
 14.82294;22.09112;13.71779;,
 10.93444;29.28505;22.23895;,
 14.67838;25.14390;24.14423;,
 14.59510;25.24988;21.18459;,
 14.78172;22.23721;24.70818;,
 17.25698;18.28896;22.64014;,
 20.84590;17.05337;20.12835;,
 22.25518;17.78945;17.62842;,
 20.65928;20.06604;16.60479;,
 16.99307;22.54952;17.65705;,
 14.59510;25.24988;21.18459;,
 -1.14229;0.32276;3.93353;,
 -1.14229;0.32276;3.93353;,
 -1.14229;0.32276;3.93353;,
 -1.14229;0.32276;3.93353;,
 -1.14229;0.32276;3.93353;,
 -1.14229;0.32276;3.93353;,
 -1.14229;0.32276;3.93353;,
 -1.14229;0.32276;3.93353;,
 17.84779;21.21438;20.79017;,
 17.84779;21.21438;20.79017;,
 17.84779;21.21438;20.79017;,
 17.84779;21.21438;20.79017;,
 17.84779;21.21438;20.79017;,
 17.84779;21.21438;20.79017;,
 17.84779;21.21438;20.79017;,
 17.84779;21.21438;20.79017;,
 13.13107;7.77530;10.19184;,
 12.57685;9.73237;8.61052;,
 0.22692;25.41257;25.93116;,
 3.89725;19.67559;27.60526;,
 11.53378;10.73078;6.47670;,
 0.19984;26.51702;19.00541;,
 6.85285;14.85673;6.18990;,
 2.17536;15.34884;9.47474;,
 3.40518;6.77841;2.70671;,
 -0.20113;8.68073;7.41877;,
 2.33573;-1.71105;3.20653;,
 -0.13202;3.96942;9.01747;,
 6.72820;0.62971;10.43578;,
 2.34221;3.97471;13.33435;,
 10.86703;7.42914;15.52656;,
 5.77216;8.69354;17.84061;,
 13.13107;7.77530;10.19184;,
 3.89725;19.67559;27.60526;,
 -0.33948;19.49364;21.46600;,
 1.64690;16.38881;22.37201;,
 -0.35413;20.09137;17.71780;,
 -0.26438;14.40894;13.26442;,
 -1.55052;10.80018;12.15174;,
 -1.51312;8.25043;13.01694;,
 -0.17407;8.25332;15.35322;,
 1.68221;10.80713;17.79200;,
 1.64690;16.38881;22.37201;,
 -0.43752;12.81410;16.18505;,
 -0.43752;12.81410;16.18505;,
 -0.43752;12.81410;16.18505;,
 -0.43752;12.81410;16.18505;,
 -0.43752;12.81410;16.18505;,
 -0.43752;12.81410;16.18505;,
 -0.43752;12.81410;16.18505;,
 -0.43752;12.81410;16.18505;;
 
 88;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 3;1,0,63;,
 3;4,1,64;,
 3;6,4,65;,
 3;8,6,66;,
 3;10,8,67;,
 3;12,10,68;,
 3;14,12,69;,
 3;16,14,70;,
 3;55,54,71;,
 3;54,56,72;,
 3;56,57,73;,
 3;57,58,74;,
 3;58,59,75;,
 3;59,60,76;,
 3;60,61,77;,
 3;61,62,78;,
 4;79,80,81,82;,
 4;80,83,84,81;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 4;87,89,90,88;,
 4;89,91,92,90;,
 4;91,93,94,92;,
 4;93,95,96,94;,
 4;82,81,97,98;,
 4;81,84,99,97;,
 4;84,86,100,99;,
 4;86,88,101,100;,
 4;88,90,102,101;,
 4;90,92,103,102;,
 4;92,94,104,103;,
 4;94,96,105,104;,
 3;98,97,106;,
 3;97,99,107;,
 3;99,100,108;,
 3;100,101,109;,
 3;101,102,110;,
 3;102,103,111;,
 3;103,104,112;,
 3;104,105,113;;
 
 MeshMaterialList {
  1;
  88;
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
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  104;
  -0.780130;0.445454;0.439282;,
  -0.868812;0.352922;0.347292;,
  -0.783304;0.453586;0.425083;,
  -0.677630;0.674393;0.293276;,
  -0.275977;-0.939484;-0.202992;,
  -0.228988;-0.745822;-0.625552;,
  -0.311756;-0.361880;-0.878551;,
  -0.381361;-0.178676;-0.906994;,
  -0.881406;0.284219;0.377284;,
  -0.959172;0.187860;0.211420;,
  -0.890865;0.352858;0.286096;,
  -0.757245;0.634444;0.155115;,
  0.038098;-0.996389;0.075874;,
  0.159178;-0.746189;-0.646424;,
  -0.018706;-0.079361;-0.996670;,
  -0.154565;0.183186;-0.970852;,
  -0.849711;0.363774;0.381654;,
  -0.887388;0.326138;0.325847;,
  -0.852496;0.375785;0.363367;,
  -0.797239;0.569828;0.199262;,
  0.281491;-0.918320;0.278302;,
  0.449436;-0.893261;-0.009655;,
  0.215611;0.145236;-0.965618;,
  0.006771;0.398583;-0.917107;,
  -0.815313;0.417101;0.401611;,
  -0.815385;0.417976;0.400555;,
  -0.814736;0.408812;0.411190;,
  -0.804076;0.551268;0.222632;,
  0.463766;-0.772112;0.434471;,
  0.663477;-0.731164;0.158734;,
  0.395392;0.331696;-0.856530;,
  0.132827;0.546449;-0.826892;,
  -0.911992;0.370428;0.176220;,
  -0.939485;0.234355;0.249891;,
  -0.902619;0.181617;0.390249;,
  -0.885601;0.260388;0.384589;,
  0.602846;-0.564786;0.563554;,
  0.810876;-0.495627;0.311180;,
  0.536966;0.498768;-0.680366;,
  0.252789;0.669236;-0.698728;,
  -0.957988;0.276543;-0.076045;,
  -0.998947;-0.008660;0.045052;,
  -0.942776;-0.077496;0.324297;,
  -0.863712;-0.063114;0.500018;,
  0.698965;-0.269347;0.662495;,
  0.957273;0.070361;0.280495;,
  0.642161;0.647680;-0.410048;,
  0.451065;0.781809;-0.430483;,
  0.727518;0.683133;-0.063610;,
  0.840173;0.431790;0.328127;,
  0.755483;0.090320;0.648912;,
  0.657250;0.053355;0.751781;,
  0.717759;0.153758;0.679102;,
  0.841489;0.431845;0.324662;,
  0.681981;0.731361;0.003545;,
  0.618683;0.777921;-0.109864;,
  -0.626184;0.575491;0.526027;,
  0.770098;0.503462;0.391758;,
  0.873191;0.102762;0.476421;,
  0.837855;0.541299;0.070668;,
  0.524386;0.771445;-0.360405;,
  -0.221560;0.659667;-0.718157;,
  -0.735753;0.216818;-0.641605;,
  -0.859918;-0.056788;-0.507264;,
  -0.201534;-0.777293;0.595987;,
  0.395710;-0.522299;0.755392;,
  -0.588946;0.531765;-0.608579;,
  -0.845133;0.195584;-0.497491;,
  -0.950783;-0.281797;-0.128850;,
  -0.364765;-0.696531;0.617892;,
  0.012050;-0.596356;0.802630;,
  -0.700755;-0.442335;0.559716;,
  -0.946814;-0.162331;0.277834;,
  -0.989462;0.092371;-0.111498;,
  -0.945454;0.257492;-0.199535;,
  -0.979638;0.183589;-0.081273;,
  -0.947727;-0.207613;0.242302;,
  -0.672858;-0.384054;0.632269;,
  -0.561867;-0.452640;0.692404;,
  -0.939253;-0.091800;0.330721;,
  -0.334048;-0.942456;-0.013687;,
  -0.085185;-0.936868;0.339148;,
  -0.639824;0.354712;0.681765;,
  -0.708141;0.196226;0.678257;,
  0.083596;-0.841672;0.533479;,
  0.401913;-0.126063;-0.906959;,
  -0.764178;0.223493;0.605047;,
  0.211457;-0.722934;0.657763;,
  0.613441;0.076600;-0.786017;,
  -0.779115;0.241521;0.578488;,
  0.329615;-0.571019;0.751859;,
  0.763354;0.271570;-0.586123;,
  -0.888524;0.381037;0.255610;,
  0.512749;-0.271928;0.814336;,
  0.811271;0.362407;-0.458804;,
  -0.877293;0.469060;-0.101688;,
  0.663992;0.731584;-0.154597;,
  0.827760;0.447357;0.338652;,
  0.702987;0.006812;0.711170;,
  -0.457319;-0.687742;-0.563800;,
  -0.466859;-0.791440;0.394544;,
  -0.608241;-0.489516;0.624833;,
  -0.944725;-0.134994;0.298782;,
  -0.964359;0.169720;-0.202994;;
  88;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;80,4,12,81;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;82,0,8,83;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;81,12,20,84;,
  4;12,13,21,20;,
  4;13,14,22,85;,
  4;14,15,23,22;,
  4;83,8,16,86;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;84,20,28,87;,
  4;20,21,29,28;,
  4;85,22,30,88;,
  4;22,23,31,30;,
  4;86,16,24,89;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;87,28,36,90;,
  4;28,29,37,36;,
  4;88,30,38,91;,
  4;30,31,39,38;,
  4;89,24,32,92;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;90,36,44,93;,
  4;36,37,45,44;,
  4;91,38,46,94;,
  4;38,39,47,46;,
  4;92,32,40,95;,
  4;96,97,49,48;,
  4;97,98,50,49;,
  4;98,93,51,50;,
  4;93,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,96,48,55;,
  3;1,0,56;,
  3;2,1,56;,
  3;3,2,56;,
  3;4,80,99;,
  3;5,4,99;,
  3;6,5,99;,
  3;7,6,99;,
  3;0,82,56;,
  3;48,49,57;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,48,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,66,60;,
  4;61,62,67,66;,
  4;62,63,68,67;,
  4;100,64,69,100;,
  4;64,65,70,69;,
  4;65,58,58,70;,
  4;101,102,72,71;,
  4;102,103,73,72;,
  4;103,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,101,71,78;,
  3;71,72,79;,
  3;72,73,79;,
  3;73,74,79;,
  3;74,75,79;,
  3;75,76,79;,
  3;76,77,79;,
  3;77,78,79;,
  3;78,71,79;;
 }
 MeshTextureCoords {
  114;
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.125000;,
  0.250000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.750000;0.125000;,
  0.750000;0.250000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}