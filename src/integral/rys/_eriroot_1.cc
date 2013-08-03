//
// BAGEL - Parallel electron correlation program.
// Filename: _eriroot_1.cc
// Copyright (C) 2013 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// The BAGEL package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the BAGEL package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <algorithm>
#include <src/integral/rys/erirootlist.h>

using namespace std;
using namespace bagel;

void ERIRootList::eriroot1(const double* ta, double* rr, double* ww, const int n) {

  constexpr double ax[1] = {5.000000000000001e-01};
  constexpr double aw[1] = {8.862269254527578e-01};
  constexpr double x[384] = {  5.171465726991715e-01, -6.993957190985554e-02,  4.840058220865065e-03, -1.150363449702610e-05, -2.907148502366769e-05,
  2.089950639734219e-06,  5.569301247750100e-08, -1.819896138117327e-08,  8.424257279799340e-10,  6.952983398979138e-11, -1.051616340890578e-11,  2.289204674733831e-13,
  3.068308595618962e-01, -3.663366103151805e-02,  3.204194498529495e-03, -1.801636190077208e-04,  2.596641029029815e-06,  6.441354100889876e-07, -7.234650334089614e-08,
  3.297196958331875e-09,  7.075647620350099e-11, -2.307094000000719e-11,  1.702473651147752e-12, -3.579235178778108e-14,  1.995727553949685e-01, -1.842332683812269e-02,
  1.494142430856725e-03, -9.997440614339429e-05,  5.020792045507433e-06, -1.355141931734192e-07, -5.220996251618817e-09,  9.780502169099166e-10, -7.134313513509531e-11,
  3.013762114549564e-12, -1.965398243028187e-14, -8.852352738330015e-15,  1.438270427284745e-01, -1.012208822324071e-02,  6.817502935926815e-04, -4.231645134690752e-05,
  2.315199163664641e-06, -1.049024154272960e-07,  3.399219424925235e-09, -2.481136261768656e-11, -6.723977866192582e-12,  6.406556401273885e-13, -3.717015992684503e-14,
  1.510137594850102e-15,  1.117430107928492e-01, -6.202443342608490e-03,  3.400703469335402e-04, -1.810466172352219e-05,  9.128714446854630e-07, -4.224946390908755e-08,
  1.721289751923488e-09, -5.720177094714830e-11,  1.208773338436666e-12,  1.562497177268355e-14, -3.523535680449469e-15,  2.406628303770788e-16,  9.127973984387489e-02,
 -4.154621335880558e-03,  1.885387010902648e-04, -8.479797807761886e-06,  3.737411043013396e-07, -1.586962244172123e-08,  6.348679110319401e-10, -2.324198711210740e-11,
  7.442277110397173e-13, -1.883904949047737e-14,  2.363427191138472e-16,  1.085419277484264e-17,  7.715076286239282e-02, -2.971355167841075e-03,  1.143639604771090e-04,
 -4.391343732362550e-06,  1.675294279806981e-07, -6.301206184011194e-09,  2.309040292528700e-10, -8.111849777302563e-12,  2.675474996228867e-13, -8.043505251002117e-15,
  2.091337199443394e-16, -4.090125618340749e-18,  6.681519585498959e-02, -2.229604651936727e-03,  7.439163912714781e-05, -2.480711616813176e-06,  8.257285236438075e-08,
 -2.735638465095516e-09,  8.972546443920589e-11, -2.888976213240463e-12,  9.024807697289825e-14, -2.693496131066532e-15,  7.523449002939389e-17, -1.904585419142487e-18,
  5.892555055557098e-02, -1.734600037488258e-03,  5.106041141526126e-05, -1.502849863398305e-06,  4.421258232998893e-08, -1.298903408465933e-09,  3.803013561297129e-11,
 -1.105506660966492e-12,  3.171382456443923e-14, -8.900882786000477e-16,  2.416173278921458e-17, -6.245504356890515e-19,  5.270462581053377e-02, -1.387924872852645e-03,
  3.654948132953807e-05, -9.624659224358162e-07,  2.534208095663163e-08, -6.670204473648560e-10,  1.753826050172921e-11, -4.600004659253957e-13,  1.200299198742754e-14,
 -3.102273009823363e-16,  7.891336222445334e-18, -1.957530906809376e-19,  4.767312922326938e-02, -1.135718599165087e-03,  2.705624162788727e-05, -6.445579984811315e-07,
  1.535486827959022e-08, -3.657552535321164e-10,  8.709841887391314e-12, -2.072501510678219e-13,  4.922621922973207e-15, -1.164878237904505e-16,  2.737573479663336e-18,
 -6.355788188337687e-20,  4.351941395804702e-02, -9.465217312415031e-04,  2.058628971526126e-05, -4.477392350611505e-07,  9.738005778990803e-09, -2.117901094882650e-10,
  4.605842859828144e-12, -1.001420812404708e-13,  2.176081904134946e-15, -4.722404058327680e-17,  1.022066314722607e-18, -2.199987629006270e-20,  4.003203844726694e-02,
 -8.009612799785000e-04,  1.602563801282234e-05, -3.206410028027197e-07,  6.415379367700991e-09, -1.283581894291149e-10,  2.568129916489605e-12, -5.137889661765264e-14,
  1.027731074467446e-15, -2.054896020236158e-17,  4.104720983665656e-19, -8.180050542402292e-21,  3.706246583253389e-02, -6.865774922505298e-04,  1.271876116321302e-05,
 -2.356134335462304e-07,  4.364708027818862e-09, -8.085556410485023e-11,  1.497830992363922e-12, -2.774656683387072e-14,  5.139674534998855e-16, -9.519337381230916e-18,
  1.762550020416397e-19, -3.260049010922107e-21,  3.450327796704970e-02, -5.950610463828389e-04,  1.026272486449138e-05, -1.769961614695875e-07,  3.052565512143844e-09,
 -5.264608119373110e-11,  9.079599717104481e-13, -1.565906421061638e-14,  2.700596433608016e-16, -4.657340825649624e-18,  8.031094368239354e-20, -1.384146328812141e-21,
  3.227486121838624e-02, -5.206977702453391e-04,  8.400537064322403e-06, -1.355277992969528e-07,  2.186501185788421e-09, -3.527532553453166e-11,  5.691048111397928e-13,
 -9.181489175519313e-15,  1.481264801410943e-16, -2.389726122346061e-18,  3.855241455663816e-20, -6.217431030113028e-22,  3.031695312954046e-02, -4.594532748729887e-04,
  6.963012110290411e-06, -1.055244141058776e-07,  1.599221971999028e-09, -2.423620085443529e-11,  3.672994855580983e-13, -5.566420588132430e-15,  8.435899705400982e-17,
 -1.278455869163044e-18,  1.937478058511703e-20, -2.935479474386447e-22,  2.858309752375132e-02, -4.084133313014822e-04,  5.835667357106542e-06, -8.338369708287320e-08,
  1.191438872735834e-09, -1.702403029578604e-11,  2.432500833431545e-13, -3.475710491950987e-15,  4.966313389866981e-17, -7.096176181586595e-19,  1.013943579232529e-20,
 -1.448478391540544e-22,  2.703690352179374e-02, -3.654303063689762e-04,  4.939149511157150e-06, -6.675745680715205e-08,  9.022925969566291e-10, -1.219537066315452e-11,
  1.648324123105114e-13, -2.227871925672716e-15,  3.011187586299683e-17, -4.069915016638208e-19,  5.500885974468628e-21, -7.433613129034288e-23,  2.564945880212885e-02,
 -3.288932830252419e-04,  4.217273840106803e-06, -5.407650311019190e-08,  6.934024916276519e-10, -8.891237186525025e-12,  1.140089625236761e-13, -1.461893687129584e-15,
  1.874530816208109e-17, -2.403639675576097e-19,  3.082095422030639e-21, -3.951402180365027e-23,  2.439750182371333e-02, -2.975747722465087e-04,  3.629500500395214e-06,
 -4.426878590183327e-08,  5.399435555957684e-10, -6.585657078402309e-12,  8.032483896177880e-14, -9.797169326067591e-16,  1.194954485881677e-17, -1.457478344586699e-19,
  1.777676927240239e-21, -2.167898397737385e-23,  2.326210525996177e-02, -2.705261783561825e-04,  3.146078669928658e-06, -3.658725768250102e-08,  4.254907664962539e-10,
 -4.948236184967182e-12,  5.754541172201184e-14, -6.692231911031617e-16,  7.782717439247921e-18, -9.050895344051385e-20,  1.052571998769989e-21, -1.223920889622860e-23,
  2.222771122371935e-02, -2.470050673708762e-04,  2.744839659505080e-06, -3.050198458106724e-08,  3.389527909806530e-10, -3.766607192662905e-12,  4.185635911934471e-14,
 -4.651280871862064e-16,  5.168728050562558e-18, -5.743740356215662e-20,  6.382721707762891e-22, -7.091912956404754e-24,  2.128141326896871e-02, -2.264236415295971e-04,
  2.409034813410579e-06, -2.563093099739561e-08,  2.727003446094602e-10, -2.901395893799993e-12,  3.086940775455204e-14, -3.284351291565484e-16,  3.494386251925879e-18,
 -3.717852992203230e-20,  3.955610425912676e-22, -4.208096190817332e-24,  2.041241452319315e-02, -2.083116364643901e-04,  2.125850317078710e-06, -2.169460932345079e-08,
  2.213966194684495e-10, -2.259384457274952e-12,  2.305734449799383e-14, -2.353035286168772e-16,  2.401306472400705e-18, -2.450567914642272e-20,  2.500839900187385e-22,
 -2.551877448242344e-24,  1.961161351381840e-02, -1.922892047385628e-04,  1.885369515003757e-06, -1.848579182039041e-08,  1.812506760650217e-10, -1.777138241803134e-12,
  1.742459889830215e-14, -1.708458237096002e-16,  1.675120078766396e-18, -1.642432467676579e-20,  1.610382694416325e-22, -1.578806563029406e-24,  1.887128390240993e-02,
 -1.780468277262464e-04,  1.679836572186345e-06, -1.584892550623520e-08,  1.495314745858076e-10, -1.410799860407534e-12,  1.331061739101463e-14, -1.255830400201479e-16,
  1.184851121282087e-18, -1.117883576776306e-20,  1.054701015913427e-22, -9.950009583923669e-25,  1.818482418633270e-02, -1.653302482984141e-04,  1.503126492856552e-06,
 -1.366591580658087e-08,  1.242458673439001e-10, -1.129601248136203e-12,  1.026995108222819e-14, -9.337090889850210e-17,  8.488966070752420e-19, -7.717879776523561e-21,
  7.016834245945910e-23, -6.378940223565131e-25,  1.754656015858991e-02, -1.539290396248875e-04,  1.350358647261168e-06, -1.184616288568197e-08,  1.039217065767921e-10,
 -9.116640723289487e-13,  7.997668708040746e-15, -7.016038769650555e-17,  6.154893608902499e-19, -5.399444983223432e-21,  4.736719723642830e-23, -4.155017301438134e-25,
  1.695158759052026e-02, -1.436678406953152e-04,  1.217611526934333e-06, -1.031948293611197e-08,  8.745952687950313e-11, -7.412356693976449e-13,  6.282109418958430e-15,
 -5.324203944993209e-17,  4.512361335562532e-19, -3.824309705833033e-21,  3.241173204684951e-23, -2.746756953122446e-25,  1.639564589459882e-02, -1.343995705282585e-04,
  1.101709848718486e-06, -9.031015396794789e-09,  7.402969047795534e-11, -6.068415157621065e-13,  4.974445021651291e-15, -4.077687935103614e-17,  3.342591751183931e-19,
 -2.740013407817476e-21,  2.246063533922800e-23, -1.841035683543226e-25,  1.587501587502381e-02, -1.260001265001900e-04,  1.000064000127500e-06, -7.937515875029766e-09,
  6.300012625023700e-11, -5.000325000963752e-13,  3.968761906277781e-15, -3.150009462522100e-17,  2.500165000647502e-19, -1.984382937521828e-21,  1.575006300017323e-23,
 -1.250005000013741e-25  };
  constexpr double w[384] = {  1.545361991220441e+00, -1.980219453337436e-01,  2.612248383778893e-02, -2.884849970973796e-03,  2.670676766446337e-04,
 -2.111301632244193e-05,  1.451410808079440e-06, -8.811300406217861e-08,  4.784657763957309e-09, -2.348708529668016e-10,  1.051546525094701e-11, -4.320417435690969e-13,
  1.023820359281469e+00, -7.784518888153107e-02,  7.624122364560783e-03, -7.022396457247253e-04,  5.777515301043659e-05, -4.211209961005566e-06,  2.730286060110980e-07,
 -1.586297668351469e-08,  8.326007203467479e-10, -3.978265968632050e-11,  1.742531851719414e-12, -7.031246318392537e-14,  7.970079097052309e-01, -3.950969305784869e-02,
  2.805999935583594e-03, -2.056406165829953e-04,  1.441048334028490e-05, -9.372763127162828e-07,  5.594257726501581e-08, -3.055973126482805e-09,  1.530178901920561e-10,
 -7.046806704995617e-12,  2.997031479439444e-13, -1.180746230988717e-14,  6.723509527749635e-01, -2.407591141126881e-02,  1.278666772987362e-03, -7.357837377974936e-05,
  4.261339325872135e-06, -2.395863459410338e-07,  1.280742031718389e-08, -6.434556820643861e-10,  3.021339691583471e-11, -1.323410182233940e-12,  5.409542892867429e-14,
 -2.064337641047958e-15,  5.921774787214273e-01, -1.649894078348730e-02,  6.877913937738493e-04, -3.163574958092680e-05,  1.504799656101738e-06, -7.172254844666060e-08,
  3.353283031936781e-09, -1.514471811286575e-10,  6.537871344370493e-12, -2.679765657446313e-13,  1.039049344757623e-14, -3.800835380518117e-16,  5.352449052014906e-01,
 -1.219218514606119e-02,  4.163325660723200e-04, -1.576962237759269e-05,  6.243326116516219e-07, -2.517955720870382e-08,  1.017000834329550e-09, -4.057418855429073e-11,
  1.580655434698953e-12, -5.958121363380983e-14,  2.158402842863696e-15, -7.472574291998652e-17,  4.921372047032724e-01, -9.479878183151961e-03,  2.738568678663404e-04,
 -8.786876848549089e-06,  2.956777650158546e-07, -1.020287518570180e-08,  3.563260205642908e-10, -1.246570476841515e-11,  4.327698839946231e-13, -1.478079224134616e-14,
  4.928448858103256e-16, -1.592741373606823e-17,  4.580278917477482e-01, -7.643351803961622e-03,  1.913026746248399e-04, -5.319549462679717e-06,  1.552723756663200e-07,
 -4.657842665839572e-09,  1.420220856137482e-10, -4.368115865709534e-12,  1.346185680564329e-13, -4.129861363466089e-15,  1.252953887453511e-16, -3.732672429585810e-18,
  4.301626319855134e-01, -6.332087512750194e-03,  1.398041568131519e-04, -3.429549457989330e-06,  8.833121026926291e-08, -2.339558719248598e-09,  6.307638480715125e-11,
 -1.720268267518487e-12,  4.723191540604572e-14, -1.299666479568216e-15,  3.567379420254427e-17, -9.712342633616481e-19,  4.068403203074891e-01, -5.357338783229481e-03,
  1.058132946123642e-04, -2.322103184678981e-06,  5.350621529332044e-08, -1.268058317257845e-09,  3.060381583269722e-11, -7.478857916501400e-13,  1.843453137679334e-14,
 -4.568561158765921e-16,  1.134799885523821e-17, -2.813955787273884e-19,  3.869457918498814e-01, -4.609438932599328e-03,  8.236006753444615e-05, -1.635074288179591e-06,
  3.408352301887205e-08, -7.307693434479426e-10,  1.595762271412849e-11, -3.529478397242439e-13,  7.879183135761312e-15, -1.770786143609973e-16,  3.997669791483280e-18,
 -9.040996479033919e-20,  3.697133073301491e-01, -4.020761648868934e-03,  6.558819925887582e-05, -1.188765693690009e-06,  2.262320897545976e-08, -4.428379132057805e-10,
  8.828767269759333e-12, -1.782979898833345e-13,  3.635070252952328e-15, -7.464382603070048e-17,  1.541057727377835e-18, -3.192404379706731e-20,  3.545972105677661e-01,
 -3.547569177209726e-03,  5.323572820068557e-05, -8.876247179971292e-07,  1.553972717099624e-08, -2.798278473492228e-10,  5.132230631518549e-12, -9.535029077804392e-14,
  1.788480718282900e-15, -3.379290491986759e-17,  6.421695848650021e-19, -1.225306778286851e-20,  3.411967022975044e-01, -3.160448469635794e-03,  4.391080913674853e-05,
 -6.778733342867154e-07,  1.098787502106924e-08, -1.831946007605244e-10,  3.110856865139695e-12, -5.351189837294712e-14,  9.293389920648787e-16, -1.625907996565235e-17,
  2.861185375247947e-19, -5.056922319011076e-21,  3.292098455955971e-01, -2.838965620737502e-03,  3.672213684272063e-05, -5.277771149836659e-07,  7.964552625636050e-09,
 -1.236249499084382e-10,  1.954427017518791e-12, -3.129942222956110e-14,  5.060675142311431e-16, -8.242972411395649e-18,  1.350520259993636e-19, -2.222586827188568e-21,
  3.184042560851505e-01, -2.568528178016353e-03,  3.107932965165038e-05, -4.178439195246218e-07,  5.898544866444772e-09, -8.564651020552699e-11,  1.266610574993063e-12,
 -1.897493185005217e-14,  2.869941607775614e-16, -4.372909768412601e-18,  6.702143230811388e-20, -1.031862641003645e-21,  3.085977624222850e-01, -2.338465923669457e-03,
  2.657983403128008e-05, -3.356826509261113e-07,  4.451373082717253e-09, -6.071459955125570e-11,  8.434531516192718e-13, -1.186950255239949e-14,  1.686397321812041e-16,
 -2.413749828901803e-18,  3.475132607966003e-20, -5.026093440963614e-22,  2.996452602123106e-01, -2.140814905389463e-03,  2.294218073851218e-05, -2.731781231413423e-07,
  3.415432424369102e-09, -4.392174276824503e-11,  5.752838066196600e-13, -7.632880778750612e-15,  1.022470235427727e-16, -1.379805666996210e-18,  1.872976029846456e-20,
 -2.554097902798464e-22,  2.914295431815748e-01, -1.969523234659971e-03,  1.996518270039426e-05, -2.248750673757183e-07,  2.659487552904296e-09, -3.235107700584230e-11,
  4.008189679926263e-13, -5.030504557084163e-15,  6.374273706580461e-17, -8.136824489734165e-19,  1.044783501857993e-20, -1.347713214613400e-22,  2.838547630790503e-01,
 -1.819918395618359e-03,  1.750221247124857e-05, -1.870208348975037e-07,  2.098339398853319e-09, -2.421562249457075e-11,  2.846323770918188e-13, -3.389040299769171e-15,
  4.074037809323376e-17, -4.933765074685110e-19,  6.010062883534241e-21, -7.355068927764324e-23,  2.768416714011880e-01, -1.688341494046408e-03,  1.544454080761653e-05,
 -1.569805518002582e-07,  1.675349663541768e-09, -1.839074240675700e-11,  2.056183339375972e-13, -2.328778547089377e-15,  2.662872932158896e-17, -3.067452097404667e-19,
  3.554285278682001e-21, -4.137521221618066e-23,  2.703240961032394e-01, -1.571890854351206e-03,  1.371028172266994e-05, -1.328699089684214e-07,  1.352059193685121e-09,
 -1.415138626920593e-11,  1.508589411053573e-13, -1.629096890588597e-15,  1.776146056646394e-17, -1.950812529177058e-19,  2.155259404616725e-21, -2.392227250896113e-23,
  2.642462914330190e-01, -1.468238900706429e-03,  1.223689804609203e-05, -1.133188947685864e-07,  1.101849225219773e-09, -1.101986423698293e-11,  1.122533006213132e-13,
 -1.158312632422013e-15,  1.206725172981286e-17, -1.266473347969773e-19,  1.336998418089759e-21, -1.418042704999582e-23,  2.585609161240256e-01, -1.375499171216056e-03,
  1.097602153097627e-05, -9.731639978166636e-08,  9.059745683561973e-10, -8.675214688454366e-12,  8.460835830453805e-14, -8.358918863822212e-16,  8.337634678800394e-18,
 -8.378007028366473e-20,  8.468095320487228e-22, -8.599207949724135e-24,  2.532274711036311e-01, -1.292128268021463e-03,  9.889809525171255e-06, -8.410596054878522e-08,
  7.510252613482619e-10, -6.897895060091179e-12,  6.452788681834095e-14, -6.114797974048087e-16,  5.850226732576242e-18, -5.638562406406574e-20,  5.466523848389668e-22,
 -5.324580806101823e-24,  2.482110781564149e-01, -1.216852564609968e-03,  8.948341339516080e-06, -7.311453853152490e-08,  6.272691018329120e-10, -5.535263886881074e-12,
  4.974982931711862e-14, -4.529483431856156e-16,  4.163529768008436e-18, -3.855491798583918e-20,  3.591245193118691e-22, -3.360816936633014e-24,  2.434815149392183e-01,
 -1.148612727030501e-03,  8.127730415994788e-06, -6.390305805720654e-08,  5.275492013452836e-10, -4.479593372741847e-12,  3.874209080051296e-14, -3.394152378594188e-16,
  3.002171780631940e-18, -2.675129767759615e-20,  2.397735847265430e-22, -2.159211544398193e-24,  2.390124450819236e-01, -1.086521233152043e-03,  7.408737175272946e-06,
 -5.613153279355574e-08,  4.465381974369900e-10, -3.653798851221779e-12,  3.045085554976376e-14, -2.570740191228576e-16,  2.191153484789428e-18, -1.881449332549872e-20,
  1.625022666280811e-22, -1.410153009024248e-24,  2.347807984068971e-01, -1.029829498326812e-03,  6.775737205372990e-06, -4.953413392933461e-08,  3.802258285608564e-10,
 -3.002015795420175e-12,  2.414088466290127e-14, -1.966514790012553e-16,  1.617324552459839e-18, -1.339992164216284e-20,  1.116746263172624e-22, -9.350804090186493e-25,
  2.307662678521608e-01, -9.779021851156547e-04,  6.215945044546663e-06, -4.390113581220908e-08,  3.255617586731961e-10, -2.483278003735166e-12,  1.929239533912196e-14,
 -1.518276238358523e-16,  1.206344549502993e-18, -9.655995521597453e-21,  7.774454324027257e-23, -6.289078729732412e-25,  2.269508979828176e-01, -9.301969444882145e-04,
  5.718824102240073e-06, -3.906568570243974e-08,  2.802032836457072e-10, -2.067213459112800e-12,  1.553339147748772e-14, -1.182363693244550e-16,  9.086399219191553e-19,
 -7.034571727399329e-21,  5.478109173434597e-23, -4.286174152758887e-25,  2.233187460129850e-01, -8.862483052146431e-04,  5.275633701685654e-06, -3.489400112802422e-08,
  2.423349082920835e-10, -1.731073583404705e-12,  1.259458737969899e-14, -9.282312716269219e-17,  6.906919268102137e-19, -5.177471118114867e-21,  3.903895319350381e-23,
 -2.957511436211931e-25  };
  int offset = -1;
  for (int i = 1; i <= n; ++i) {
    double t = ta[i-1];
    offset += 1;
    if (t < 0.0) {
      fill_n(rr+offset, 1, 0.5);
      fill_n(ww+offset, 1, 0.0);
    } else if (t >= 64.0) {
      t = 1.0/sqrt(t);
      for (int r = 0; r != 1; ++r) {
        rr[offset+r] = ax[r]*t*t;
        ww[offset+r] = aw[r]*t;
      }
    } else {
      int it = static_cast<int>(t*   0.500000000000000);
      t = (t-it*2.000000000000000-   1.000000000000000) *   1.000000000000000;
      const double t2 = t * 2.0;
      for (int j=1; j <=1; ++j) {
        const int boxof = it*12+12*(j-1);
        double d = x[boxof+11];
        double e = w[boxof+11];
        double f = t2*d + x[boxof+10];
        double g = t2*e + w[boxof+10];
        d = t2*f - d + x[boxof+9];
        e = t2*g - e + w[boxof+9];
        f = t2*d - f + x[boxof+8];
        g = t2*e - g + w[boxof+8];
        d = t2*f - d + x[boxof+7];
        e = t2*g - e + w[boxof+7];
        f = t2*d - f + x[boxof+6];
        g = t2*e - g + w[boxof+6];
        d = t2*f - d + x[boxof+5];
        e = t2*g - e + w[boxof+5];
        f = t2*d - f + x[boxof+4];
        g = t2*e - g + w[boxof+4];
        d = t2*f - d + x[boxof+3];
        e = t2*g - e + w[boxof+3];
        f = t2*d - f + x[boxof+2];
        g = t2*e - g + w[boxof+2];
        d = t2*f - d + x[boxof+1];
        e = t2*g - e + w[boxof+1];
        rr[offset+j-1] = t*d - f + x[boxof+0]*0.5;
        ww[offset+j-1] = t*e - g + w[boxof+0]*0.5;
      }
    }
  }
}
