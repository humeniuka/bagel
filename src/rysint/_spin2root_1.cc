//
// BAGEL - Parallel electron correlation program.
// Filename: _spin2root_1.cc
// Copyright (C) 2013 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
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
#include <src/rysint/spin2rootlist.h>

using namespace std;
using namespace bagel;

void Spin2RootList::spin2root1(const double* ta, double* rr, double* ww, const int n) {

  constexpr double ax[1] = {2.500000000000000e+00};
  constexpr double aw[1] = {6.646701940895685e-01};
  constexpr double x[384] = {  1.328131665580148e+00, -5.174757555994045e-02, -1.461325278278165e-03,  7.301731444313293e-05,  6.622090874809514e-06,
 -5.082132221841281e-08, -2.501061248784544e-08, -5.559707324692380e-10,  7.526801887971758e-11,  4.269755730235632e-12, -1.524875246446046e-13, -2.037498725953055e-14,
  1.105480184926600e+00, -5.842345371367089e-02, -8.869243792959951e-05,  1.389382374217188e-04,  8.036404955207344e-08, -5.010039455139302e-07,  1.031249952147384e-10,
  1.930411914904706e-09, -1.228663909124681e-12, -7.556243329728993e-12,  6.862084621446923e-15,  2.981885892876370e-14,  8.800538084414160e-01, -5.312173960832696e-02,
  1.299921018093112e-03,  7.572935155267626e-05, -6.446523959986176e-06, -5.181453038621299e-08,  2.465577157875637e-08, -5.696864400793154e-10, -7.343602817745412e-11,
  4.316682490510310e-12,  1.426125987480761e-13, -2.032107459388712e-14,  6.917567881626046e-01, -4.075028901792743e-02,  1.637654939666308e-03, -1.182985686854525e-05,
 -3.597180143328466e-06,  2.295936210581365e-07, -1.157891754898426e-09, -6.591358966220180e-10,  3.767250977181377e-11,  1.590426732206572e-13, -1.272449487434735e-13,
  5.962696121346469e-15,  5.530987051467184e-01, -2.887788786441295e-02,  1.285403516365791e-03, -3.816146511328371e-05, -1.394165787351279e-07,  9.905405084061955e-08,
 -6.045598903456943e-09,  1.308393196556280e-10,  7.332829536093272e-12, -7.875888931041631e-13,  2.945511804346953e-14,  2.070892680753696e-16,  4.553425462654938e-01,
 -2.035779407338897e-02,  8.578966722768028e-04, -3.096286661556460e-05,  7.416305945167500e-07,  5.904031948695587e-09, -1.865229118939510e-09,  1.132195934403843e-10,
 -3.656572395704796e-12,  6.777708093149906e-15,  6.969361987898226e-15, -4.570470248090698e-16,  3.855666843372447e-01, -1.478150746640783e-02,  5.559615976216683e-04,
 -1.972890723880790e-05,  6.059653700856233e-07, -1.265016164169735e-08, -8.386694912439676e-11,  2.593836926571707e-11, -1.564465046144583e-12,  5.860225409600993e-14,
 -1.192129988741892e-15, -1.877132323248192e-17,  3.340441803571550e-01, -1.113502926086501e-02,  3.691615106861521e-04, -1.200004546130142e-05,  3.694701282718928e-07,
 -9.991158535222182e-09,  1.922497721066334e-10,  4.581677332907520e-13, -2.806646072999089e-13,  1.687670298875256e-14, -6.660309315818745e-16,  1.832123101082984e-17,
  2.946225118319764e-01, -8.670833571963948e-03,  2.548285425396127e-04, -7.444646369408098e-06,  2.134070972330324e-07, -5.825779763064022e-09,  1.420081941881382e-10,
 -2.600866669254736e-12,  5.937162780879036e-15,  2.439507055392567e-15, -1.488840034702004e-16,  5.950680965839183e-18,  2.635222851204571e-01, -6.939272366935875e-03,
  1.826695860519052e-04, -4.800732941473376e-06,  1.254141040851064e-07, -3.219678215813503e-09,  7.918774854833648e-11, -1.768184879961476e-12,  3.127176026433810e-14,
 -1.920599744503856e-16, -1.719389964449953e-17,  1.107216128406562e-18,  2.383655126838009e-01, -5.678536949796192e-03,  1.352687054527609e-04, -3.220907206657331e-06,
  7.656131168627355e-08, -1.809539202214690e-09,  4.210844306703926e-11, -9.443676617731801e-13,  1.952879895281150e-14, -3.349675372525224e-16,  2.987775591730117e-18,
  9.546243055048320e-20,  2.175970490028206e-01, -4.732599874929172e-03,  1.029294754793486e-04, -2.238396565422221e-06,  4.865580715029924e-08, -1.055826782510828e-09,
  2.279235289099908e-11, -4.853876262372298e-13,  1.001824447824558e-14, -1.933150139458404e-16,  3.214668265428253e-18, -3.459681784171463e-20,  2.001601890370964e-01,
 -4.004805042043611e-03,  8.012788315299153e-05, -1.603158094644483e-06,  3.207149684777975e-08, -6.412938169826733e-10,  1.280259030862237e-11, -2.544053766659519e-13,
  4.996839959652673e-15, -9.560135744651355e-17,  1.730605843885458e-18, -2.784274436717430e-20,  1.853123286753093e-01, -3.432887253580620e-03,  6.359375864370894e-05,
 -1.178059915749884e-06,  2.182270028975737e-08, -4.041999662958919e-10,  7.483148503292400e-12, -1.383366048017856e-13,  2.547041961461262e-15, -4.643572395489592e-17,
  8.283183468362475e-19, -1.411959685305217e-20,  1.725163897616498e-01, -2.975305200446243e-03,  5.131361714449822e-05, -8.849796986402963e-07,  1.526269849180816e-08,
 -2.632183725076004e-10,  4.538865592298065e-12, -7.823325763779991e-14,  1.346699796072661e-15, -2.310183540601793e-17,  3.930389827487722e-19, -6.566159109841365e-21,
  1.613743060808999e-01, -2.603488846496308e-03,  4.200268423869354e-05, -6.776388285422987e-07,  1.093248629159605e-08, -1.763747879711535e-10,  2.845380467229380e-12,
 -4.589785190832822e-14,  7.400725890614568e-16, -1.191966690840441e-17,  1.914174011411136e-19, -3.052235451482953e-21,  1.515847656460596e-01, -2.297266373658753e-03,
  3.481506038927787e-05, -5.276220452912126e-07,  7.996106897699760e-09, -1.211807256069361e-10,  1.836475580417822e-12, -2.783063606229528e-14,  4.217089358587277e-16,
 -6.387801269117481e-18,  9.666466536630677e-20, -1.458888784360791e-21,  1.429154876185134e-01, -2.042066656402622e-03,  2.917833676140201e-05, -4.169184816476244e-07,
  5.957193920102973e-09, -8.512010960251407e-11,  1.216247120949794e-12, -1.737833025269833e-14,  2.483025755579520e-16, -3.547403322655739e-18,  5.066501157856982e-20,
 -7.228705080047357e-22,  1.351845176089329e-01, -1.827151531829415e-03,  2.469574755221551e-05, -3.337872834769619e-07,  4.511462918787778e-09, -6.097684706598676e-11,
  8.241615680345342e-13, -1.113932623460763e-14,  1.505574038939180e-16, -2.034853767339411e-18,  2.749953443242980e-20, -3.714713346554253e-22,  1.282472940106390e-01,
 -1.644466415123937e-03,  2.108636920000843e-05, -2.703825154685018e-07,  3.467012448374876e-09, -4.445618500549357e-11,  5.700447391920806e-13, -7.309463451670017e-15,
  9.372624498793790e-17, -1.201804246168186e-18,  1.540973848675817e-20, -1.975383939336404e-22,  1.219875091185659e-01, -1.487873861232211e-03,  1.814750250189904e-05,
 -2.213439294970562e-07,  2.699717776541674e-09, -3.292828525520582e-11,  4.016241839461498e-13, -4.898583923660949e-15,  5.974768027925443e-17, -7.287368451216345e-19,
  8.888274017737418e-21, -1.083901529258769e-22,  1.163105262998087e-01, -1.352630891780864e-03,  1.573039334963205e-05, -1.829362884107341e-07,  2.127453832270665e-09,
 -2.474118090474457e-11,  2.877270570110675e-13, -3.346115846413348e-15,  3.891358068442594e-17, -4.525444219501001e-19,  5.262843534147330e-21, -6.119533292964328e-23,
  1.111385561185967e-01, -1.235025336854374e-03,  1.372419829752376e-05, -1.525099229050782e-07,  1.694763954872526e-09, -1.883303596037640e-11,  2.092817953624055e-13,
 -2.325640419907984e-15,  2.584363929425032e-17, -2.871869668630704e-19,  3.191358418615647e-21, -3.545945921294409e-23,  1.064070663448436e-01, -1.132118207647984e-03,
  1.204517406705266e-05, -1.281546549869406e-07,  1.363501723042831e-09, -1.450697946857194e-11,  1.543470387385609e-13, -1.642175643439535e-15,  1.747193111915755e-17,
 -1.858926421276238e-19,  1.977804854461961e-21, -2.104046537498443e-23,  1.020620726159658e-01, -1.041558182321950e-03,  1.062925158539351e-05, -1.084730466172486e-07,
  1.106983097341599e-09, -1.129692228631262e-11,  1.152867224849958e-13, -1.176517642743024e-15,  1.200653234150100e-17, -1.225283946378407e-19,  1.250419897556645e-21,
 -1.275938495307937e-23,  9.805806756909202e-02, -9.614460236928140e-04,  9.426847575018780e-06, -9.242895910195128e-08,  9.062533803250148e-10, -8.885691209006677e-12,
  8.712299449078992e-14, -8.542291184984430e-16,  8.375600390850416e-18, -8.212162322441051e-20,  8.051913395399225e-22, -7.894032480513273e-24,  9.435641951204965e-02,
 -8.902341386312319e-04,  8.399182860931726e-06, -7.924462753117589e-08,  7.476573729290246e-10, -7.053999302036372e-12,  6.655308695496898e-14, -6.279152000935673e-16,
  5.924255605978271e-18, -5.589417881567095e-20,  5.273505068415397e-22, -4.975004743209827e-24,  9.092412093166349e-02, -8.266512414920707e-04,  7.515632464282760e-06,
 -6.832957903290434e-08,  6.212293367194985e-10, -5.648006240680826e-12,  5.134975541112593e-14, -4.668545444914756e-16,  4.244483035313759e-18, -3.858939887926829e-20,
  3.508417121356540e-22, -3.189470104704619e-24,  8.773280079294955e-02, -7.696451981244373e-04,  6.751793236305840e-06, -5.923081442840986e-08,  5.196085328839602e-10,
 -4.558320361644716e-12,  3.998834354020158e-14, -3.508019384823788e-16,  3.077446804442250e-18, -2.699722491563380e-20,  2.368359861587826e-22, -2.077508649694712e-24,
  8.475793795260129e-02, -7.183392034765760e-04,  6.088057634671666e-06, -5.159741468055986e-08,  4.372976343975156e-10, -3.706178346988220e-12,  3.141054709479184e-14,
 -2.662101972496390e-16,  2.256180667779972e-18, -1.912154852909560e-20,  1.620586602308812e-22, -1.373378476413401e-24,  8.197822947299412e-02, -6.719978526412928e-04,
  5.508549243592432e-06, -4.515507698397395e-08,  3.701484523897767e-10, -3.034207578810532e-12,  2.487222510825641e-14, -2.038843967551777e-16,  1.671295875591780e-18,
 -1.370006703907739e-20,  1.123031766956561e-22, -9.205178417503374e-25,  7.937507937511906e-02, -6.300006325009500e-04,  5.000320000637501e-06, -3.968757937514883e-08,
  3.150006312511850e-10, -2.500162500481876e-12,  1.984380953138890e-14, -1.575004731261046e-16,  1.250082500323724e-18, -9.921914687607708e-21,  7.875031500079676e-23,
 -6.250025000038161e-25  };
  constexpr double w[384] = {  2.263881670308705e-01, -7.179973691078170e-02,  1.310022611239201e-02, -1.713865677452399e-03,  1.760154638907506e-04,
 -1.492181753600646e-05,  1.078514626015634e-06, -6.798635444904323e-08,  3.801412732599497e-09, -1.910223000848757e-10,  8.717376670083458e-12, -3.638952638029034e-13,
  6.474999092672383e-02, -1.736445538953048e-02,  2.826030162475050e-03, -3.413642964458648e-04,  3.308461918751246e-05, -2.685105063451345e-06,  1.876212098765901e-07,
 -1.151331049912998e-08,  6.298510508311076e-10, -3.108367007046949e-11,  1.397161487259340e-12, -5.757639499532383e-14,  2.338243266075153e-02, -5.048879851827366e-03,
  7.025179122023503e-04, -7.584235841973539e-05,  6.772120561071593e-06, -5.169675882520658e-07,  3.446838173240551e-08, -2.038866981018388e-09,  1.083111801978559e-10,
 -5.218951760249158e-12,  2.299881045052955e-13, -9.321979130417798e-15,  1.050484182702601e-02, -1.794848488925064e-03,  2.070178668294664e-04, -1.934793538756945e-05,
  1.548537936535516e-06, -1.087697405498975e-07,  6.802518088206435e-09, -3.827829446149337e-10,  1.954554886603072e-11, -9.122533258639643e-13,  3.916714400868554e-14,
 -1.553689391130535e-15,  5.599365995119615e-03, -7.679157754550478e-04,  7.287736201029026e-05, -5.780383204952303e-06,  4.049132547003882e-07, -2.557858924757868e-08,
  1.471150189592424e-09, -7.747928976421089e-11,  3.753239857455982e-12, -1.679188306251565e-13,  6.965941054469584e-15, -2.686446923097412e-16,  3.370838299362747e-03,
 -3.815061598520083e-04,  3.016399031030817e-05, -2.025764050438349e-06,  1.226488886716919e-07, -6.846571747526387e-09,  3.554514073132839e-10, -1.721875575086387e-11,
  7.794045475764376e-13, -3.300287791758649e-14,  1.309040886180749e-15, -4.866286935061855e-17,  2.209855508384067e-03, -2.121135885275116e-04,  1.426115552022278e-05,
 -8.197300098168411e-07,  4.292572085906704e-08, -2.101704783577328e-09,  9.725652123748186e-11, -4.269517898327421e-12,  1.779030769615384e-13, -7.031784646395291e-15,
  2.634608172248296e-16, -9.343704014855539e-18,  1.540389574862047e-03, -1.282295988895830e-04,  7.480407009800615e-06, -3.738531664686055e-07,  1.709444921938513e-08,
 -7.359288663082591e-10,  3.023488960439560e-11, -1.192363610964211e-12,  4.521102107391432e-14, -1.647266838716635e-15,  5.758558862857019e-17, -1.926451131111255e-18,
  1.124100100680026e-03, -8.259051298523595e-05,  4.252031464417829e-06, -1.876472160375245e-07,  7.587333238589073e-09, -2.896611284985083e-10,  1.060281422231770e-11,
 -3.750747914014958e-13,  1.286771026982568e-14, -4.284393999858432e-16,  1.383171343345129e-17, -4.318261344994945e-19,  8.499373745517458e-04, -5.588289504930093e-05,
  2.574183126200094e-06, -1.016543697922960e-07,  3.679546302984007e-09, -1.258753661318894e-10,  4.136606769747381e-12, -1.317978271427540e-13,  4.091962916450404e-15,
 -1.240837785822547e-16,  3.676363066679463e-18, -1.062420974790020e-19,  6.610653366334263e-04, -3.932959395561419e-05,  1.639076754316081e-06, -5.856048772943833e-08,
  1.917943693208868e-09, -5.938458030345312e-11,  1.767498186144878e-12, -5.107035424952869e-14,  1.441127919213295e-15, -3.985354204390047e-17,  1.081870850057270e-18,
 -2.881662727370655e-20,  5.261553883218645e-04, -2.858357716005524e-05,  1.087610900452115e-06, -3.547700490220514e-08,  1.060849234856635e-09, -2.999171654088945e-11,
  8.152428741521919e-13, -2.152273817620455e-14,  5.554182442385740e-16, -1.406842548861681e-17,  3.506413446668324e-19, -8.605312453829245e-21,  4.268814776225895e-04,
 -2.133660463565779e-05,  7.468931515766933e-07, -2.241294778226877e-08,  6.165549921613524e-10, -1.603589342722697e-11,  4.010309739046544e-13, -9.742071647184132e-15,
  2.314065940367946e-16, -5.398489301471631e-18,  1.240601251677377e-19, -2.812303818274532e-21,  3.519903695165273e-04, -1.629096136668350e-05,  5.280157318869713e-07,
 -1.467056193450562e-08,  3.736599304672669e-10, -8.998198847747292e-12,  2.083551665076524e-13, -4.686623871599912e-15,  1.030889134934025e-16, -2.227577497741753e-18,
  4.743568218331801e-20, -9.972608597581840e-22,  2.942872485252832e-04, -1.268149627614074e-05,  3.826740190600125e-07, -9.898765175085700e-09,  2.347256855278886e-10,
 -5.262459741497319e-12,  1.134456041289098e-13, -2.375737776333754e-15,  4.865402233437217e-17, -9.789033743104109e-19,  1.941244758407736e-20, -3.801965481412744e-22,
  2.490124178195478e-04, -1.003853802854255e-05,  2.833734806413123e-07, -6.857036632277779e-09,  1.521035310794320e-10, -3.189993587703921e-12,  6.432960642208040e-14,
 -1.260215830840406e-15,  2.414304275528109e-17, -4.544117519930721e-19,  8.430417185240214e-21, -1.544912134072234e-22,  2.129237423997936e-04, -8.063673364064242e-06,
  2.138279319559840e-07, -4.860492989544584e-09,  1.012791650538039e-10, -1.995293489783939e-12,  3.779755032403656e-14, -6.955582676207638e-16,  1.251748991660767e-17,
 -2.213166827281175e-19,  3.857091794062887e-21, -6.640390407819586e-23,  1.837561578969285e-04, -6.561548130166143e-06,  1.640512599571456e-07, -3.515877522506549e-09,
  6.907333538977349e-11, -1.283019662739758e-12,  2.291532485554648e-14, -3.975864297116299e-16,  6.746073293506713e-18, -1.124564537907683e-19,  1.847858130124362e-21,
 -2.999573822557436e-23,  1.598917554160837e-04, -5.400885437093500e-06,  1.277323903878075e-07, -2.589495229175708e-09,  4.812276214901264e-11, -8.455350039293893e-13,
  1.428506198076998e-14, -2.344473375708131e-16,  3.762897382751301e-18, -5.933533187907945e-20,  9.222651535577429e-22, -1.416178709679367e-23,  1.401520549929737e-04,
 -4.491407051312306e-06,  1.007749601225136e-07, -1.938199050648224e-09,  3.417153460604781e-11, -5.696075098231521e-13,  9.129692305050235e-15, -1.421507125154391e-16,
  2.164490737562419e-18, -3.237996102789325e-20,  4.774725760774352e-22, -6.955858001253879e-24,  1.236635932665965e-04, -3.769740914985511e-06,  8.045627535532388e-08,
 -1.471911649355634e-09,  2.468442849091396e-11, -3.913894392055608e-13,  5.967110737668842e-15, -8.837540291766485e-17,  1.280007190168382e-18, -1.821408052431535e-20,
  2.554780587593608e-22, -3.540289114686233e-24,  1.097688181643827e-04, -3.190576529111464e-06,  6.492781474114863e-08, -1.132567175107974e-09,  1.810989514432798e-11,
 -2.737866238410063e-13,  3.979946878575177e-15, -5.620235429413049e-17,  7.761494387516674e-19, -1.053052369168420e-20,  1.408335320826870e-22, -1.860836865085955e-24,
  9.796572697204299e-05, -2.720976247438762e-06,  5.291032123783300e-08, -8.819135485806611e-10,  1.347503102253255e-11, -1.946603674828927e-13,  2.703920262251837e-15,
 -3.648566711590801e-17,  4.814644586041086e-19, -6.241944531086373e-21,  7.976769130625989e-23, -1.007132592835227e-24,  8.786617289986003e-05, -2.336634901442614e-06,
  4.350302808876967e-08, -6.942512791046190e-10,  1.015620535971595e-11, -1.404720711510267e-13,  1.868172239822368e-15, -2.413547292459414e-17,  3.049356326460657e-19,
 -3.785072672475247e-21,  4.631180232331269e-23, -5.598442662575445e-25,  7.916655575911574e-05, -2.019371006075873e-06,  3.606160470761940e-08, -5.520028556950136e-10,
  7.745593364534237e-12, -1.027570299427900e-13,  1.310800713132289e-15, -1.624327800054384e-17,  1.968448655200598e-19, -2.343625137845051e-21,  2.750448958867235e-23,
 -3.189202043645050e-25,  7.162688668674117e-05, -1.755413308641430e-06,  3.011847085404776e-08, -4.429479614743063e-10,  5.971578615198265e-12, -7.611475688374287e-14,
  9.328605486648125e-16, -1.110647884731856e-17,  1.293151520243225e-19, -1.479231143688416e-21,  1.667915442820565e-23, -1.858143979172221e-25,  6.505561484667338e-05,
 -1.534211058640470e-06,  2.532980158727998e-08, -3.584625234234500e-10,  4.650203931465124e-12, -5.703524489505793e-14,  6.726399592641932e-16, -7.706084243331806e-18,
  8.633723759497501e-20, -9.503336772248532e-22,  1.031111020475613e-23, -1.105365596507808e-25,  5.929848242532637e-05, -1.347595329297903e-06,  2.143968109315077e-08,
 -2.923759010166261e-10,  3.654944205430591e-12, -4.319791920671225e-14,  4.909223979706268e-16, -5.419691171593520e-18,  5.851261394751573e-20, -6.206374888431113e-22,
  6.489000808270151e-24, -6.703356317663398e-26,  5.423023731127108e-05, -1.189179522284027e-06,  1.825547559719939e-08, -2.402163347320358e-10,  2.897527305995061e-12,
 -3.304420302035764e-14,  3.623521817024255e-16, -3.859918172616696e-18,  4.021041409285910e-20, -4.115404352554132e-22,  4.151812952546623e-24, -4.138479334860786e-26,
  4.974840047670351e-05, -1.053925303874501e-06,  1.563066913533855e-08, -1.987047582913473e-10,  2.315550742314908e-12, -2.551190809041468e-14,  2.702709422177604e-16,
 -2.781424903175374e-18,  2.799294034463510e-20, -2.767854106959420e-22,  2.697672063585015e-24, -2.597859389077074e-26,  4.576852918375175e-05, -9.378245622061328e-07,
  1.345274046235738e-08, -1.654101874713655e-10,  1.864355941049834e-12, -1.986725592335676e-14,  2.035704067732347e-16, -2.026296184913416e-18,  1.972442610222903e-20,
 -1.886337073984245e-22,  1.778220012790854e-24, -1.656283694782421e-26,  4.222058176840047e-05, -8.376637870948888e-07,  1.163449409036652e-08, -1.385118805033477e-10,
  1.511615744059951e-12, -1.559689512113930e-14,  1.547399794515246e-16, -1.491345957307605e-18,  1.405618315424668e-20, -1.301577012929481e-22,  1.188019550788592e-24,
 -1.071427089101464e-26  };
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
        ww[offset+r] = aw[r]*t*t*t*t*t;
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