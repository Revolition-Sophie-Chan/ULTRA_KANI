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
 -6.69786;4.12195;1.99996;,
 -6.49197;5.06930;1.37888;,
 -6.85852;6.31343;2.77207;,
 -7.23897;4.56297;3.91966;,
 -6.74418;5.77897;0.50806;,
 -7.32454;7.62471;1.16299;,
 -0.70570;5.02020;-4.32255;,
 -2.90530;8.95941;-4.03667;,
 -4.24042;2.46201;-5.61773;,
 -9.43662;4.23248;-6.42986;,
 -5.66465;-0.02554;-4.86858;,
 -12.06825;-0.36392;-5.04562;,
 -4.14408;-0.98528;-2.51394;,
 -9.25859;-2.13727;-0.69481;,
 -0.56944;0.14501;0.06687;,
 -2.65353;-0.04877;4.07392;,
 -6.69786;4.12195;1.99996;,
 -7.23897;4.56297;3.91966;,
 -7.95634;7.89044;4.55769;,
 -8.45341;5.60334;6.05709;,
 -8.56521;9.60372;2.45533;,
 -6.14940;13.14292;-2.06747;,
 -14.68297;6.96688;-5.19433;,
 -18.12136;0.96140;-3.38573;,
 -14.45037;-1.35560;2.29888;,
 -5.82045;1.37314;8.52952;,
 -8.45341;5.60334;6.05709;,
 -9.61826;9.56026;6.46390;,
 -10.15629;7.08472;8.08684;,
 -10.27731;11.41471;4.18832;,
 -9.94410;16.93382;1.28526;,
 -19.18077;10.24893;-2.09923;,
 -22.90244;3.74864;-0.14161;,
 -18.92901;1.24074;6.01136;,
 -9.58805;4.19431;12.75536;,
 -10.15629;7.08472;8.08684;,
 -11.59130;11.06867;8.20048;,
 -12.08838;8.78158;9.69989;,
 -12.20018;12.78195;6.09813;,
 -13.71170;19.75498;5.51110;,
 -22.24527;13.57894;2.38424;,
 -25.68366;7.57347;4.19285;,
 -22.01267;5.25645;9.87745;,
 -13.38275;7.98521;16.10809;,
 -12.08838;8.78158;9.69989;,
 -13.18837;26.34413;24.85003;,
 -13.02049;20.88274;25.18664;,
 -13.19851;27.25249;19.45158;,
 -16.87861;21.17691;9.96670;,
 -23.40992;16.44998;7.57351;,
 -26.04154;11.85358;8.95776;,
 -23.23190;10.08022;13.30856;,
 -16.62684;12.16871;18.07729;,
 -13.02049;20.88274;25.18664;,
 -16.62706;22.66783;20.87360;,
 -16.53620;19.71214;21.05577;,
 -16.63256;23.15943;17.95199;,
 -18.96270;20.98313;13.97375;,
 -22.49742;18.42494;12.67856;,
 -23.92165;15.93738;13.42771;,
 -22.40108;14.97765;15.78235;,
 -18.82644;16.10792;18.36316;,
 -16.53620;19.71214;21.05577;,
 0.11454;1.92499;-2.88157;,
 0.11454;1.92499;-2.88157;,
 0.11454;1.92499;-2.88157;,
 0.11454;1.92499;-2.88157;,
 0.11454;1.92499;-2.88157;,
 0.11454;1.92499;-2.88157;,
 0.11454;1.92499;-2.88157;,
 0.11454;1.92499;-2.88157;,
 -19.64669;19.20313;16.92219;,
 -19.64669;19.20313;16.92219;,
 -19.64669;19.20313;16.92219;,
 -19.64669;19.20313;16.92219;,
 -19.64669;19.20313;16.92219;,
 -19.64669;19.20313;16.92219;,
 -19.64669;19.20313;16.92219;,
 -19.64669;19.20313;16.92219;,
 -14.82015;9.14966;3.23553;,
 -14.52162;7.40158;5.10449;,
 -3.95700;23.11449;23.54051;,
 -6.89461;25.33040;17.57000;,
 -13.62873;5.17174;6.03646;,
 -4.13666;16.12226;24.05365;,
 -9.47978;4.44976;10.64969;,
 -4.86021;7.58557;11.96788;,
 -5.12553;1.57244;2.77315;,
 -1.72323;6.03644;5.47958;,
 -3.04028;2.74674;-5.45710;,
 -1.20965;8.01840;0.94469;,
 -7.60422;9.84818;-3.05398;,
 -3.62033;12.37043;1.01968;,
 -12.47402;14.44683;3.61054;,
 -7.54312;16.54318;5.66063;,
 -14.82015;9.14966;3.23553;,
 -6.89461;25.33040;17.57000;,
 -2.73254;19.14063;17.37597;,
 -4.32238;20.33987;14.14474;,
 -2.82979;15.35646;17.65367;,
 -2.28497;11.38847;11.64628;,
 -0.58725;10.55009;8.13485;,
 -0.30930;11.62271;5.68058;,
 -1.61396;13.97801;5.72117;,
 -3.73695;16.23628;8.23282;,
 -4.32238;20.33987;14.14474;,
 -1.89055;14.42620;10.33471;,
 -1.89055;14.42620;10.33471;,
 -1.89055;14.42620;10.33471;,
 -1.89055;14.42620;10.33471;,
 -1.89055;14.42620;10.33471;,
 -1.89055;14.42620;10.33471;,
 -1.89055;14.42620;10.33471;,
 -1.89055;14.42620;10.33471;;
 
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
  2;
  88;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.608000;0.008000;0.008000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  104;
  0.762674;0.453769;0.460894;,
  0.854835;0.359938;0.373768;,
  0.765620;0.439787;0.469482;,
  0.652920;0.312977;0.689740;,
  0.308886;-0.224817;-0.924147;,
  0.256877;-0.642684;-0.721784;,
  0.327358;-0.885746;-0.329074;,
  0.390731;-0.909339;-0.142942;,
  0.869668;0.388285;0.304816;,
  0.951333;0.220457;0.215323;,
  0.877110;0.298860;0.375979;,
  0.734388;0.174244;0.655983;,
  -0.004107;0.051096;-0.998685;,
  -0.130964;-0.665367;-0.734939;,
  0.025221;-0.998227;-0.053921;,
  0.151873;-0.965307;0.212407;,
  0.835240;0.394466;0.383106;,
  0.874402;0.337923;0.348179;,
  0.837682;0.376493;0.395654;,
  0.776411;0.216969;0.591701;,
  -0.250809;0.254252;-0.934051;,
  -0.418418;-0.033778;-0.907626;,
  -0.216796;-0.962736;0.161673;,
  -0.016976;-0.907018;0.420749;,
  0.798955;0.415571;0.434708;,
  0.799000;0.414537;0.435612;,
  0.798627;0.424940;0.426171;,
  0.783793;0.239906;0.572812;,
  -0.438597;0.413128;-0.798096;,
  -0.638546;0.137559;-0.757190;,
  -0.403296;-0.849920;0.339098;,
  -0.148386;-0.813772;0.561923;,
  0.898039;0.189551;0.396984;,
  0.929914;0.259969;0.260148;,
  0.894348;0.398810;0.202710;,
  0.874653;0.395018;0.280967;,
  -0.585214;0.546636;-0.598927;,
  -0.794536;0.295079;-0.530699;,
  -0.551201;-0.670352;0.496796;,
  -0.272985;-0.683178;0.677308;,
  0.948196;-0.064735;0.311019;,
  0.998475;0.049479;0.024471;,
  0.943640;0.326676;-0.053157;,
  0.863459;0.502329;-0.045858;,
  -0.691809;0.652386;-0.309503;,
  -0.960188;0.277682;0.030526;,
  -0.662482;-0.396936;0.635263;,
  -0.476034;-0.413166;0.776328;,
  -0.750328;-0.050129;0.659162;,
  -0.855766;0.334760;0.394463;,
  -0.760609;0.647415;0.048244;,
  -0.661556;0.749798;0.012128;,
  -0.725203;0.679337;0.112168;,
  -0.857070;0.331291;0.394560;,
  -0.706730;0.018405;0.707244;,
  -0.644640;-0.093526;0.758744;,
  0.604018;0.542975;0.583387;,
  -0.788439;0.400465;0.466896;,
  -0.874067;0.484304;0.038173;,
  -0.895927;0.043206;0.442096;,
  -0.616954;-0.411729;0.670707;,
  0.133145;-0.774419;0.618504;,
  0.697531;-0.672342;0.247804;,
  0.855046;-0.518543;0.003141;,
  0.299672;0.653617;-0.694968;,
  -0.322105;0.803819;-0.500123;,
  0.514370;-0.662310;0.544765;,
  0.810203;-0.529262;0.251898;,
  0.976285;-0.124861;-0.176852;,
  0.452263;0.665425;-0.593858;,
  0.068152;0.849046;-0.523904;,
  0.754696;0.579601;-0.307402;,
  0.962366;0.270611;-0.024906;,
  0.969991;-0.139153;0.199385;,
  0.905556;-0.239547;0.350122;,
  0.949620;-0.116337;0.291012;,
  0.968324;0.238914;-0.072588;,
  0.720789;0.647673;-0.246946;,
  0.619476;0.715528;-0.322908;,
  0.946967;0.317662;0.048428;,
  0.366304;-0.035374;-0.929823;,
  0.116052;0.316330;-0.941524;,
  0.624648;0.693282;0.359409;,
  0.698385;0.686184;0.203495;,
  -0.056641;0.512161;-0.857020;,
  -0.393882;-0.911655;-0.117224;,
  0.753731;0.613931;0.234477;,
  -0.188982;0.638738;-0.745855;,
  -0.612713;-0.786738;0.075006;,
  0.768141;0.587893;0.253657;,
  -0.312650;0.736001;-0.600460;,
  -0.770001;-0.582798;0.259703;,
  0.873918;0.269067;0.404808;,
  -0.506196;0.804983;-0.309465;,
  -0.821497;-0.453501;0.345659;,
  0.861028;-0.085999;0.501233;,
  -0.688160;-0.139596;0.712004;,
  -0.843936;0.345723;0.410181;,
  -0.705511;0.707837;-0.034934;,
  0.482839;-0.578456;-0.657461;,
  0.562609;0.448579;-0.694441;,
  0.669211;0.650277;-0.359577;,
  0.957238;0.289279;0.003655;,
  0.934814;-0.236163;0.265235;;
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