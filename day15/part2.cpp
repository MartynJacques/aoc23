#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

struct step_t {
  char op;
  std::string label;
  int focal_len;
};

std::vector<std::string> split(const std::string& target, char c) {
  std::string temp;
  std::stringstream stringstream{target};
  std::vector<std::string> result;

  while (std::getline(stringstream, temp, c)) {
    result.push_back(temp);
  }

  return result;
}

int hash(std::string const& label) {
  int curr = 0;
  for (int i = 0; i < label.size(); i++) {
    int c = label.at(i);
    int ascii = (int)c;
    curr += ascii;
    curr *= 17;
    curr = (curr % 256);
  }
  return curr;
}

step_t parse_step(std::string const& input_step) {
  if (input_step.find('=') != std::string::npos) {
    auto eq_split = split(input_step, '=');
    return {'=', eq_split[0], std::stoi(eq_split[1])};
  }
  return {'-', split(input_step, '-')[0], -1};
}

int main() {
  std::string input =
      "vvkcff=7,qsm=6,zfsz=4,kbg=3,cs-,gvh=1,dct=4,bsg-,vqq=5,gl-,trhc-,gvh=4,"
      "xf-,gtkl=9,trbd=8,qbscx-,bz=4,zh-,xbx=5,dzd=9,msrgsb=9,xrf=8,sr=1,gfcql="
      "6,vvtdp=7,zdc=9,xxk=1,jbh=5,njc=2,njn-,vcm-,qx=8,lkl-,nkqs-,ldd-,lfz=3,"
      "qvnq-,llg=6,sg-,bl-,xxk-,gt=8,cbp-,pzxc-,kqbt=2,cpq-,fttkg-,jsr-,lkl-,"
      "xkx=5,hzst-,qtt-,jcxr-,psmm-,njc-,qhnr-,hlk-,xr-,bvpqdj-,fhv=2,fttkg-,"
      "jz-,bz=8,tppcb-,vgfr-,jjlrr=2,lfz-,szfq=9,bls=2,qdq-,svcb=9,zgb=3,cf=2,"
      "gttk-,lqn=3,zsgct-,ltj-,zdtkk-,mh-,rms-,khl-,nks-,ss-,cntk=5,bs=6,gqg-,"
      "db-,zzq-,rpp-,vt=6,fpxz-,vjvm=4,vkz-,vdj=4,hgf=9,sks=2,hlk-,zv=9,vdm-,"
      "nvsr=8,sks=4,cbp=3,kqbt-,cl=8,rmh-,ps=9,pn=6,frp-,zbmts-,njn=2,mstnpg=1,"
      "bn=3,cbf=4,chdk-,qpllk=3,zc=8,sgklt=4,qn=8,ct=5,zq-,mv-,cclj=5,kz-,hlk="
      "2,kgn-,pv-,pctvf-,qvnq=5,px=9,zx-,nvf=4,hlk-,lx-,bxc=9,dz-,gr=2,qhnr-,"
      "llqt-,qp-,jsr=2,btdxxp-,kp-,nzl=7,tjl=3,njn=2,pgx=1,rg=6,qdq-,qsm-,qbx-,"
      "zv=9,bnf=7,vvtdp-,dfsb-,srr=1,rktk-,qdk-,rhlv-,cdk-,fdjf=8,pd=3,mqg-,tz="
      "2,frm-,vc=7,ldd-,mz=1,dq=1,klc-,tmn-,sb=6,vhtd-,gvk-,sgl=1,jzl-,bxc=4,"
      "ldd-,xqdtf-,vt-,hs-,kkrnf=1,cs-,bsl=6,kxg-,zhc-,dxr-,qct-,lrhgd=1,sf-,"
      "hdf-,fd=5,tc=3,gvk=7,hzm=7,xgcpp=6,hdf-,hdf-,sb-,df=6,pdlz=1,kn=5,frm=9,"
      "xpdrm-,gjmjrv=5,kqgq=6,pk-,fb-,bgt=7,vfdlhq=4,zbmts-,vv=1,zccc=9,np-,"
      "sjlk=8,tss=8,mv=2,pxpr=5,cxmp=3,bxc=4,dhs=4,gtzk-,ljg=2,kcp=5,zdc-,tqjb="
      "7,qdk=7,lx=1,dxz-,ht=1,vvkcff-,xqdtf=2,djd-,trjtl-,pd-,qq=1,kqgq-,tcv=3,"
      "cdk-,kxg=7,bxc-,kz-,czt-,mkc=4,tp-,vdm=4,bjng-,sdhl-,gm-,czt=1,mjt=7,lj="
      "9,lztjd=5,djd-,jd-,dcdrv=8,tflk=4,mstnpg-,hnsghx=8,vjk-,zsn-,vl-,hdf=8,"
      "njn=7,sf-,hb=1,hzm=5,dx=8,mxg=6,chdk=4,jz-,mstnpg-,vp=6,gfcql-,zsbj-,dz="
      "6,msrgsb=6,ztt=5,mpg=3,sjlk-,rq=9,bsl=8,qh=5,vd=8,njn-,pdlz-,lqn-,ncft="
      "9,pm=8,mfb=8,xg=5,jd=3,sqkc=8,pd-,fr=5,khl-,pctvf-,kqnjk=2,kxg-,ldc-,"
      "gft-,dbg=4,cxzq-,fb-,hb=5,kqgq-,qbx-,qvnq-,ql-,cdgvf=6,kcp-,gjz-,kqgq=8,"
      "mnz=9,mt-,nlxbzc=2,zstl-,lm-,bx=3,qbm=5,zhc-,jcxr-,cf-,vqp-,hqbmx-,dqj-,"
      "qxp=3,qhg=2,pk-,qpllk-,dhs=1,phr=2,ngmd=6,ltj-,pctvf-,zq-,ncft=4,mzr=5,"
      "cs=4,nvf-,pgx=5,ktt-,gvh=5,ztt-,vkm=4,scb-,jqk=1,qxp=5,fp=1,pm=1,bz=6,"
      "vpd=1,cjd-,czt=4,mx-,bvj-,hs-,mpg=1,tcv=7,hz=3,lztjd-,gvh=3,gt-,tr-,qbm-"
      ",gxh-,tflk-,rjtl=8,cnb-,ss=7,xn=7,qbscx-,xpm-,fhb-,gbb=3,tmn=4,jkm-,lfz-"
      ",jrg-,xk-,zgb=4,rmh=3,zvc=7,sbvx-,zr=3,kkrnf-,kbg-,vkm-,dt=4,fd-,ckm=6,"
      "dbg=6,zkpz=1,gx=6,xn=3,kblbg=7,lls-,xxk=7,zdnd-,zvtkxm=7,kn-,qct-,tflk="
      "4,qq-,dzd=2,bsgjn=5,bnf-,czt-,xt=7,jjlrr-,zbmts-,dxhg-,hd-,qbscx=5,"
      "pctvf=7,dqdv=3,kg-,ps=3,bx=6,pctvf-,mt=3,jmjm=1,gnh-,hk-,tlk=4,vpd-,vbg="
      "4,pp=7,jrg=4,vvh=7,jrg-,njc=8,kgn-,kxg=8,tmn-,px=6,qsm-,bl=6,jd=7,kg=1,"
      "dr=4,hqcqb-,ldc-,dxhg=7,xrt=6,zh=4,cf=2,kcp-,mstnpg=1,px-,lffflt-,dz-,"
      "qds-,kblbg-,pdlz=9,jpb=6,qdk=8,rcm=2,vtng=7,mchc=8,zdtkk-,qmlf-,xm=5,"
      "qvccp-,qjzk=1,mjt=4,pqdl=8,sdhl-,gtkl-,chdk=4,trhc=7,mnz-,ztt-,hzst-,"
      "cpqh=2,vdj=3,qjzk-,ql-,gdt-,lqv=8,zdtkk-,trbd-,srr-,zbzv=8,kbg-,vp-,mtr-"
      ",qvccp=3,rq-,cntk=1,phr=5,qj-,gqh=9,mm-,tppcb-,jgpjxb-,gbb-,fd-,frvv=5,"
      "khl-,btdxxp=5,pz-,rpp=5,ltvf=4,dqsq-,fc-,nvf=1,lqv-,cjd=5,nn-,tj-,qbx-,"
      "db=3,nq=6,lq-,ntpn=5,dxjtjb-,tqcxq-,gg-,qvs=8,qjzk-,vvkcff-,vtln-,zstl-,"
      "xmprb-,ts-,mc-,tp-,dt-,cntk-,tflk=9,dfpx=2,xmprb=3,dkc-,qdgm-,gxh-,zccc-"
      ",qrprpd-,pxpr=7,qklv-,gnh-,vbg=5,dcdrv-,gft=6,nvj-,zdc-,kbg-,qq-,zbmts="
      "1,sjlk-,qklv-,jz=4,chdk=3,mxg-,gvh=5,lls=9,zprzq=4,llqt=6,dbg-,ngxq-,ds="
      "9,tn-,hzst-,ztt=8,vkm-,khl=4,jmf-,ztt=3,pz=3,ldc-,xpdrm=7,dp-,xhbs-,mv="
      "1,tmn=5,rms-,pbpxf=1,kcp=8,zsn=3,vv-,gvh-,ln-,cdk-,sb=8,rqr-,nzl=4,lqn="
      "4,vd-,qhg-,hcqh-,mrb-,zdc-,pp-,xkx=7,klc-,lls-,klc-,cxzq-,kblbg=8,qhgf="
      "9,jzl-,zbmts-,cgv=9,qcfz-,rzkc=6,qdk-,hzm-,pd-,fb-,bxc-,ctf=2,vvkcff-,"
      "pd-,qk-,pqdl=2,rg=1,hb=1,mtr-,pjc-,sp-,mtr-,hdf=7,jkm-,rj=9,pn=2,qpllk-,"
      "mc-,gbb-,qdk-,ft=7,cc-,vjk=3,xn-,vjvm-,gx=4,dxr=6,stv-,bvd=8,xhbs=3,lq="
      "9,mzp=1,kp=2,vvh-,qvnq=6,qvs-,ncft=1,pbpxf-,tsz-,mzp=4,nlxbzc=8,vvkcff="
      "1,tlk-,xms-,tjl-,scb=2,gbb=5,qtt=6,tqcxq=8,bp=6,hs-,cbf=9,msrgsb-,ccvd="
      "1,gbx=9,tjl-,pdlz=1,zprzq=8,khl=4,dll-,tvjb=6,pjc=9,ntpn=1,trhc-,mchc=6,"
      "gtcgmx-,djd-,xpdrm-,xrt-,cs-,mx=8,mz=5,ldd-,szfq=9,np=6,xkx-,sgl=7,qdk="
      "3,fb-,kq=8,djd-,lz=7,gt=1,bls-,sp-,ldc-,vp=8,vm-,fcn-,hkjk-,rng-,jd-,tc="
      "7,czt-,pch=2,mng-,vv=6,pjb=6,pn=1,xms=9,vbsz-,qj-,ft-,tqcxq=3,mzt=7,bs-,"
      "hb=8,qjzk=7,cclj-,bbl-,gl-,vmkb=9,pbbmt=6,nvc-,nks-,qhnr-,cgv=1,rzkc-,"
      "zq=8,kt=7,kgn-,gvk-,zdnd-,qpllk-,rcrfs-,ln-,xpdrm=6,qx-,gjmjrv-,zq-,vpd="
      "5,vj-,rdl=6,lq=4,lg=2,dgcgc=2,njc=4,ldc=9,nff-,cx=1,cf=4,gxh=1,dzd=8,tb-"
      ",qk=5,ft=3,vp-,mjt=6,tppcb=2,qrprpd-,xpm=6,kjxx=2,tp=5,hkjk=3,gg-,kd=8,"
      "tss=5,ph-,zjn=3,xhbs=6,nvj-,qqzt=7,rcm-,vzd=7,cpq=5,sbvx=4,hhtb=3,xhbs="
      "9,bxc-,lkl-,cntk-,mh-,tmn-,trhc-,msrgsb=3,gh=2,bls=6,vqq-,qq-,rpp=3,qdq="
      "1,zfsz-,xrf-,hqbmx-,lnh-,lrf=6,zl-,gft=8,czt=2,jcxr-,lffflt=5,cf=4,mrrj-"
      ",qq=9,kn-,bf-,frp-,frp=4,nn=7,vtlv-,dl=2,sb=4,ckm-,zstl-,kcp-,hzm=7,rj="
      "8,rcm=2,hsxn=5,mzr=8,gm=6,gft-,pkr-,dt=8,xv-,pn=6,sxj=1,bgt=7,qdq-,cn-,"
      "df-,gbx-,kcp-,qhgf=3,rqr-,fb=5,kblbg-,rdl-,pmd-,kjxx-,lffflt-,jjqmb-,"
      "rmh=8,dct-,gt=4,hjc=4,ds=1,mkc-,fdjf-,qdq=2,zvtkxm=6,pbpxf-,gh-,qklv=8,"
      "rb-,dzd=6,jjlrr-,qvs-,ht-,xms-,bx-,kblbg-,frp-,ph-,gl=9,bz-,xn=1,btdxxp="
      "5,zx-,tqjb-,fc=1,mpg=7,cjd-,szp=8,mg=1,kq=3,mrrj-,px-,hgf-,dqr-,dgs=6,"
      "gr-,rms=9,lrhpc=4,dct-,srr=2,kxg=6,bvj-,ztqc=9,jqk-,czt-,gnh-,dl-,tr-,"
      "jgpjxb=9,jjqmb=1,gdt=6,ljg=5,sr-,jd=1,xlhxd-,tbspnx-,rsmvds=2,vvtdp=6,"
      "mng-,hhtb-,rhlv=9,hqbmx=8,vtng=1,xmprb-,ltvf-,qjzk=1,btdxxp-,rpp-,bsl-,"
      "gjz=2,mknpz-,vtlv-,ql-,hnsghx=8,rktk-,jpb=6,xk-,vdm-,mkc=4,qbx-,zhc-,"
      "pgx-,pbbmt-,phr-,sjlk=6,db-,pz-,cbf=9,jqk=9,kg-,fp-,khl=4,njc-,xrf=6,mx="
      "6,xpdrm-,ztqc=8,ss-,dhs-,cmq-,kqbt-,xg-,rsmvds-,hsxn=5,vmf-,zp=4,qdgm-,"
      "szp-,jllf=5,ltvf=3,tflk-,chdk-,rb=3,cxzq-,ldd=9,xms=8,qq-,kqnjk=9,kg=5,"
      "tmn=9,hfcm=7,frvv=1,hsxn-,fhb-,hd=5,znc=9,chdk-,hnzjq-,zsgct=1,qmlf=3,"
      "vmkb-,qqzt-,ktskt=9,vm-,qh=8,jz-,vv-,bz-,vc=2,zqbqz=2,vpd=2,nks-,jjqmb="
      "8,cnr=4,gnh=5,nvj-,ss-,bls-,kdplr-,hnsghx-,vt=3,cf-,lgp=9,ft=4,rcl-,bz-,"
      "lfpjzc=5,qbfzcq=3,xrt=3,zx-,dxr-,gvh=5,mlkg=6,zstl=9,fr=9,vqq=6,kd=5,"
      "czt=2,xkx-,lffflt=6,th=7,tbspnx-,ztqc-,kqbt-,ph-,cdgvf=6,xznps-,rhlv=2,"
      "xznps=5,mzp-,czt=5,pc-,tlk-,sr-,dll-,xms-,rcl-,xv=4,pc=6,lj=1,lrhgd-,"
      "scg=1,mrb-,nvf-,zkpz=2,trjtl-,mknpz-,mx=5,dfpx=7,mrb-,srr=1,fv-,jrg=7,"
      "slb=7,jbh=8,znc-,lrhpc-,kz=1,qvccp-,db-,zccc=1,zr-,vd-,pmd-,qhnr-,lrhgd-"
      ",ct=8,zzq=5,cdgvf=1,jcxr=3,qcqt=2,jcxr-,gfcql=5,cpq=3,hgnr-,ctf=1,trjtl-"
      ",rc-,tz-,gtzk=7,btdxxp=8,ntpn-,cbf=8,vjk=2,scb-,rq-,dbg-,xg=4,jllf=7,"
      "dqdv-,nvf=8,jllf=8,khl-,nzl=4,qrprpd=5,xm=9,rpp=3,nr-,dcdrv-,bkl-,"
      "vvkcff=7,lztjd-,xpm-,jkm=3,dttz=9,zfsz=8,hn-,vvh=2,pc-,cx=4,vrv=3,vv-,"
      "cdd-,pkr-,cn-,pd-,fv=5,rtm-,qhg-,pbpxf=2,bl=2,cbp=5,svcb-,sr=5,gq-,gqg="
      "1,fttkg=2,ts-,bsgjn-,trjtl=7,hjc=1,zprzq=6,mmx-,dpfnqr-,dm=5,lx-,xrt=7,"
      "qjzk-,kg-,cclj=7,mxg=5,qvccp=9,cc-,mchc=9,tbspnx=1,bd=2,tqjb=4,kqnjk=8,"
      "df-,pdk-,qsm=7,szfq-,dct-,ss=2,kg=5,bx=5,hjc=9,rg=7,hfcm=1,dp-,txx=5,vp="
      "4,vl=3,fr-,jb-,gbx-,vmkb=8,gg-,gz-,klc-,lkl-,xr-,mrrj-,gfcql=3,kt=8,cjd="
      "7,pmd=6,pzxc=8,trhc=8,sqkc=4,qdgm-,qcfz-,gg-,pgx-,mfb-,vzldq-,df-,lrhgd="
      "2,bbl=4,mknpz=7,kblbg-,nff-,rmh=3,sjlk=3,kz=6,cclj-,dr=6,kcp=5,qdk-,"
      "mrrj-,xr=4,nvf=5,hfcm-,hzm-,sbvx-,mt=2,gjz=9,frm-,vtln-,fgb=3,qh-,bsgjn="
      "4,vh-,lm-,pbbmt=1,zprzq=2,pjb-,sjlk-,mg=5,tl-,jmf-,kg-,dkc-,hbbl=6,mng="
      "9,ct=7,zr-,vfdlhq=1,sqkc=6,fc-,kqbt-,fc-,sdhl-,bs-,zbzv-,mng-,xpdrm-,"
      "rcm=3,rsbz=4,rtm-,dt=1,nks=2,kblbg-,vgfr=6,jzl-,bsgjn-,sks-,rms=7,gt-,"
      "pd=4,szp-,rmh-,sqkc=7,hjc-,zfsz-,jvd=8,mkc-,qk-,rq=8,fdz-,hnsghx-,bgt-,"
      "jt=4,sjlk=6,dttz-,jzl-,mxg-,cnb=7,lpchk-,zbmts-,bf-,mrrj=7,gttk=4,fp=4,"
      "lrhgd=9,kqgq=4,sv-,mh-,frp-,gb-,rcm-,bx=8,rjtl=5,pctvf=5,bxc=1,vtb-,"
      "ggvcqj-,rzkc=4,ntpn=1,sqkc=9,svcb=3,bp=3,gtkl-,stv-,jllf-,cxmp=2,cb=9,"
      "qmlf=8,vcm=1,nlxbzc=9,vh=7,qvccp=4,xn=2,ft=2,qklv=2,hbl=8,ct=6,ntn-,dxr-"
      ",sjn-,hgnr-,pjc=2,gfcql-,cn-,lgp=6,sv-,hn=6,mzp=5,hsxn-,qhg-,qbm=6,tl-,"
      "bjng=8,xqdtf-,trbd-,dttz-,sjn=2,vvtdp=1,sgl-,pkr-,rcrfs-,cpqh-,nvc-,jb="
      "3,tqjb-,hzm=1,pzxc-,xqdtf-,lqv=9,ct=5,kbg=3,ts-,qjzk=9,dqj-,phr=3,rtm=5,"
      "gr=1,rmh-,rmh=1,zbzv=6,xxk=6,vp=9,qklv=3,sjn-,dx=6,hbl=5,tj-,rmh-,dqr-,"
      "vl=4,fhv=6,mlkg=9,cxmp-,tp-,fgb=1,bx-,qdk-,qvnq=4,zgb-,lnh-,nrsgfn-,"
      "kblbg=8,tb=9,rms-,cn-,vfdlhq-,trjtl=1,ss=2,gdt=9,chdk=7,lpchk=1,bsgjn=7,"
      "gm-,vzd-,mrrj-,mrrj=9,pm-,qhgf=7,gxh=1,mz=1,lfz=4,lx-,kfdb-,rdl=5,mnz=7,"
      "hk=7,hzm-,bsgjn-,dfpx=9,lqv-,rng=6,zsbj-,jsm=9,tcv-,zdtkk=8,zjn-,dqr=6,"
      "xr-,bnf=9,zh=9,sjn=4,vtng=9,fv=9,lfpjzc-,dqsq-,lztjd=7,nq-,kg-,btdxxp=8,"
      "qj=4,bg-,lztjd=8,rktk-,mknpz-,qbx=6,rsbz-,bg=1,cl=5,zvc-,bls-,qq=8,dxr="
      "4,zl=4,mzr=4,mm=2,nxtt-,zq-,scb-,cnb-,rjtl=3,jgpjxb-,cc-,qj-,ht-,qn-,"
      "bsl=5,cxzq=4,gft-,cgv-,vl-,qvccp-,zdc=6,cn-,dl-,rms=3,hfcm=6,gg-,sf=3,"
      "jqk-,cs=4,gvh=3,srr=8,pgx-,fv=2,tss-,gjmjrv-,pq=6,dfpx=9,zh-,vjk-,dfsb-,"
      "xf-,db=6,hnzjq=3,vm-,dxjtjb-,tj=1,njn=5,cbf-,vtng-,trbd=5,ljg=2,vzd=6,"
      "ln-,pz-,qpllk-,bsg=7,vfdlhq=8,tpg=4,xk-,cd-,xxk=8,zc-,dpfnqr-,szp-,tlk-,"
      "vcm=4,dqr-,bg=5,kgn=2,szfq-,nlxbzc=2,sp=1,gr=8,qds-,ngxq=3,kgn-,qbscx=5,"
      "tlk-,jb-,ccvd-,vvkcff=2,nvc=4,ntpn-,zgb-,qn-,dxz-,fdjf=2,xxk=6,tn-,mp-,"
      "ngxq=3,hqkg-,cntk-,hzst=3,lls-,znc=4,ntpn=2,dll=1,vgfr=7,vkm=3,dttz-,"
      "dqj=6,zbzv-,hqkg=3,sjn-,rc=4,ktskt=8,qk=9,cbf-,fdjf-,dpfnqr=7,qct=7,qdq-"
      ",mknpz=6,llqt-,mchc-,tmn-,cj-,hd=9,sp=5,dxr=6,dr-,xznps=1,dp-,vvh=7,gm-,"
      "tfm-,ldd-,hqcqb-,kgn=6,jz-,vpvjp-,gft-,rg=6,msrgsb=8,ccvd-,rtm-,qbm=1,"
      "zl=6,sg=6,mt-,pch-,hkjk=1,svcb=7,trhc=6,gvh-,zjn=5,ptpr=4,ql-,blllmg-,"
      "jjlrr-,tc-,kqgq=3,rhlv=3,hb=1,rcm=3,tp-,cdd-,gbx=2,kcp-,ct-,pz-,ps=7,qp-"
      ",dct-,rktk=1,cmk=9,np=3,ss-,jvd=1,xhbs=7,kqnjk=1,hd=9,szfq=7,zfsz=6,qn-,"
      "xqdtf=2,qp=2,dz-,lg-,th=7,trbd=1,vtlv-,qvccp=1,ggvcqj=7,kqgq-,lrhgd=6,"
      "mv=3,xk-,bsg-,dl=2,qxp=7,dxjtjb=1,gq-,fpxz=1,mstnpg-,pctvf-,rcrfs-,ttj-,"
      "nr-,gttk=8,mrb=9,pzxc-,kg=1,xrt=9,pp-,scb-,zkpz=1,kdplr-,vt=5,rsmvds-,"
      "bg-,pkr=4,qbx=1,zdtkk-,mm-,cj-,rpp=1,hjc-,qtt-,kz=2,hsxn-,gdt-,sxj-,"
      "cclj-,rcrfs=5,cxzq-,gq-,qdgm-,cpqh=1,hk=1,zsn-,rktk=4,fgb-,tflk=3,mzp=9,"
      "hbl-,dqdv=9,qsm=6,chdk-,zx=3,kt=6,cd-,klc=2,qklv-,dkc-,nqcfs=2,vvkcff-,"
      "klc-,sks=5,gbx=3,lrhpc=6,rj=4,kbg-,mp-,tfm-,hnzjq-,bn=2,bp=8,mxg-,rhlv-,"
      "zstl=6,lm=2,pgx-,mrb=7,xr-,mfb-,ngxq-,mp-,mnz=1,vhtd-,cl=1,lm-,hbbl-,"
      "mtr=4,dct-,vv-,qhnr=2,khl=4,xznps-,ts-,znc=3,hsxn=4,msrgsb=9,cpqh-,"
      "xlhxd=2,ldd=9,pn-,nxtt-,dttz-,pz-,ckm-,gr=8,lx-,qt=3,dll-,sv=1,dxr-,"
      "qcqt-,pc=4,qrprpd-,nrsgfn-,cd-,kd=7,vkm-,zx=3,rp-,mg-,bkl=4,mh=8,vm-,"
      "mstnpg=3,dxz-,qn=1,qdgm=7,tp-,rktk=9,qbfzcq=6,vpvjp-,slb=2,fdjf=3,gjdbf-"
      ",dxblpb=5,qct=5,vp-,vdj=9,bkl-,dhs-,gx-,bnf=6,lq-,pxpr-,mtr=5,jt=1,dr=7,"
      "txx=9,cpqh=9,rg-,zv=1,fb=4,lx=4,pz=6,mrrj-,th=9,zjn-,qklv=9,ht-,qjzk=4,"
      "mfb=8,bf=2,qds=1,gl-,cs=6,chdk=7,qmlf-,cn=3,nrhbm=3,btdxxp-,mng-,mmx-,"
      "ptpr=7,rp-,zsbj-,mng-,vtng-,sr=2,srr-,fttkg=6,ldd=9,qbfzcq-,rg-,fpxz=5,"
      "mnz-,nzl=7,kdplr=5,cntk-,hfcm=7,qdq=3,vrv=2,rcrfs-,hn=1,bnf-,hs=4,jvd=6,"
      "ljg=9,dttz=7,vzldq=7,bl=4,vvkcff=4,zq-,kblbg-,fhv=3,qp-,kdplr=9,pz-,mkc="
      "3,fdz-,zbzv=9,nrnx=5,fhb-,qxp-,fcn=6,pch-,pp=1,gr-,tvjb=2,vhtd-,bvj-,sr="
      "6,mm=1,vjvm=5,nq=4,lz-,frp=1,jd-,vzd-,np-,bs-,dgcgc-,jrg-,xn-,pch-,pkr="
      "7,vj=6,phr-,vtng=2,tqjb-,dpfnqr-,mtr=6,ldd=7,zdtkk=6,tsz=9,gqh=8,xf=2,"
      "hnzjq-,kfdb-,jmf=9,hqbmx-,ss=1,qvnq-,xqdtf-,pm=9,qbx-,nlxbzc=5,mqg=2,gx-"
      ",sjn=7,xpm=4,bz-,cnb=2,zh-,px-,zjn-,pjb-,ct-,zhc=1,rcm-,mz=5,hlk=4,tss="
      "1,zh-,vkm-,gtkl=9,dx=4,psmm-,jsm=3,xqdtf=9,qmlf=7,mng-,mng=3,qp=2,jbh-,"
      "bvpqdj-,tqcxq-,vhtd-,ljg=2,ft=2,sdhl-,pn-,mrrj=4,qklv-,hgnr-,pp-,ccvd=3,"
      "db-,lq-,ktskt=6,nn=7,sgl-,mzt-,gqh=4,dqr-,tpg=6,ph-,mchc=7,zsgct-,jzl-,"
      "ccvd-,ln=8,fb-,gl-,cmk-,dqr=7,vjk-,pjc=1,mm=5,vqp=3,bgt=2,zdc-,zccc-,"
      "zdnd-,vvh=8,pn=2,tcv=9,zvc=4,qqzt-,kblbg=4,qbx-,qbx=7,mrb=4,lrhgd-,"
      "jjlrr-,bls=9,jt-,xqdtf-,gttk-,xmprb-,scg=7,qq-,nr-,gjdbf-,rq=8,mkc=1,lx="
      "6,jrg=1,pch-,gvk=2,pgx-,vkm=6,th=8,zp-,jpb-,vzd-,czt-,fhb-,tvjb=3,cf=4,"
      "pxpr-,pbbmt-,jkm-,hd-,vv=8,tppcb-,vpvjp-,fdjf-,ggvcqj-,xms-,kd=9,qds=5,"
      "jmjm=3,kcp=7,gkbl-,trbd=1,nzl-,dxblpb=4,gjz=9,lqn=8,vbg-,ds=8,jqk=2,"
      "jmjm=7,ntpn=1,bkl-,lgp-,vhtd=3,tcv=3,hs-,zgb-,gjdbf=8,pq-,kkrnf=2,pq-,"
      "dkc-,zl-,gg-,ctf=3,vvh-,mm=3,vm-,zsgct-,px-,dbg-,pdk=9,sgl=1,qvs=4,xpm-,"
      "rms=1,gjdbf-,gdt-,mstnpg=4,dxblpb-,qds=4,dgcgc=1,sjlk=3,hhtb=9,ptpr-,"
      "mchc=5,dll=4,vhtd-,lrf-,zvc-,mh-,mx-,lgp=7,cx=6,njc=9,nq=6,czt=6,sbvx=5,"
      "xqdtf-,kv=9,qx=4,tbspnx-,xlhxd-,tppcb=5,tlk-,zh=6,zzq-,cclj-,jcxr=6,bnf="
      "3,zkh-,dqdv-,qvnq=7,dx=7,dbh=4,nks=4,xlhxd-,ztqc=9,ggvcqj-,ngxq-,cmq-,"
      "lztjd-,cjd-,rdl=6,ngxq-,pq-,vbsz-,hnsghx=5,bgt-,jmjm-,cn-,gb=3,tfm=3,ss="
      "6,xrt=3,vqp=7,slb=9,zdtkk-,zh=6,qds=5,kdplr=6,dxjtjb-,qds=3,mzt-,hsxn=9,"
      "qdq-,rng-,zzq=1,cn=3,sjn=2,lq-,kfdb=6,qn-,mstnpg-,vvtdp-,klc=6,mp-,"
      "zprzq-,rc=3,njc=4,pbpxf-,sqkc-,lkl-,vtb=6,xrt=3,gnh=3,kp-,pv-,gr=8,rms-,"
      "zjn-,frm-,cxzq-,pdlz=1,vm-,vv=3,ztt=7,hd-,xlhxd-,vmkb-,sp=7,kjxx=8,tmn-,"
      "dzd=5,bkl-,mnz-,bp=8,rp-,bvj-,vkz-,qbscx-,mz-,rg=6,qsm=5,mtr=9,dgs=2,"
      "gjdbf-,gb-,kd=4,kqgq-,vj=8,qrprpd-,xrt-,qcfz=4,kg-,tqjb-,gbx-,pc-,pk-,"
      "bjng-,bs=2,tn-,dttz-,lfpjzc-,pd=1,pxpr-,vkm=8,cb=6,scb=5,tj=6,zjn=3,cgv-"
      ",jkm=9,jrg=6,qn=7,kdplr=7,xm=1,lx-,zprzq-,hsxn-,qn=9,fhv-,bxc=5,px=4,"
      "nrhbm-,lrf=9,ql-,jsm=4,vj-,dll=8,qbx-,kfdb=1,hkjk-,jvd=5,bz=3,qmlf=9,"
      "zsb-,dgs-,gh=5,qk=6,zsn=4,pjc=7,gbx=9,nr=5,ldc-,tqjb=9,lrhgd=8,jcxr=2,"
      "zfsz=9,lls-,trhc=4,nks-,nn=8,rzkc-,kqbt-,cntk-,vqp-,zx=3,zzq=2,mfb-,"
      "mrrj=2,bs=7,xr-,fv-,chdk=6,xk-,ds-,vv-,dx=7,bvd=2,kd=4,vcm=3,vdj=2,qp=7,"
      "ss-,nrhbm-,mlkg-,vd=3,mtr-,fhv=2,kq=1,hqkg-,gqg=2,jsr-,jqk-,kv=8,cbf-,"
      "dbh=8,cclj-,rhlv=7,gttk=4,vpvjp-,qct=2,nlxbzc=8,zhc-,pmd=7,rjtl-,qp=3,"
      "dp-,ds=8,ql=7,mng=1,hb-,fcn-,kz=2,ctf=5,kblbg-,zbzv-,hk-,cb-,mjt=4,cnb-,"
      "hdf=2,nvj-,sv-,gjmjrv-,rhlv-,gb-,lrhpc=7,nr-,gh-,mh-,jsm=5,bp-,dxhg=1,"
      "gbx-,cbf-,gkbl=9,dxjtjb-,vjk=7,zsn=1,mxg-,bx=7,qcfz=8,cc=8,scb=8,qct=1,"
      "hqcqb-,hzm-,tqcxq-,xqdtf=7,zsb=7,kv=1,frp-,bgt=9,qt=4,ntpn=3,qn=3,sjlk="
      "1,qbx=7,qjzk-,gdt=6,dq=3,dt=3,rqr=7,bkl=8,rcrfs-,ltj=7,ztqc=2,zgb-,pv=4,"
      "cjx-,svcb-,tppcb-,stv-,xgcpp-,rdl=8,dqr=8,scb=6,xg-,qtt=4,zx=3,zzq=9,"
      "kbg=9,hnzjq-,tqjb-,ngxq=7,qjzk-,tqjb=9,qdgm-,vfdlhq-,bls-,lm-,bsg=8,jbh="
      "1,llqt=2,cmq-,gz=2,frvv=2,gg-,zprzq-,zv-,cx-,cjx-,bsg-,qhnr-,tflk=5,"
      "vgfr-,vvh-,kcp=6,ltvf-,ljg-,tmn-,gdt=5,dct-,ntpn-,cx-,nqcfs=5,hk-,frm=2,"
      "djd=1,bl-,qbscx-,dxjtjb=1,dxz=8,hqcqb-,xpm-,gtkl-,hhtb=5,rdl=2,dxr=7,"
      "jzl=8,nqcfs-,qhgf-,mtr=1,sf-,sq=8,kd=6,gr=4,vrv-,zdtkk=4,cd=1,hqbmx-,"
      "vvtdp=7,fp-,jqk=1,zgb=3,tppcb-,tb=2,ntn-,mrb=5,rcl=7,pk=7,gb-,cl=7,cl-,"
      "dpfnqr-,rktk-,frm-,vdj=2,zbzv=2,hnsghx=8,jpb=3,qdgm=1,lrhpc-,zhc-,znc-,"
      "mp=8,jcxr=8,xbx-,np=7,tr=9,mv-,chdk-,klc=9,zr-,nvc=5,kcp-,mh-,vbg-,mtr="
      "7,xg-,klc=3,ggvcqj-,mzr-,vmkb-,frp=1,djd-,zstl-,ggvcqj-,hdf=4,kgn=5,vzd="
      "5,cf=4,vfdlhq=2,bvd-,hgnr=2,scb=5,lx=1,qds-,mjt-,bp=3,vtng=1,zdc=6,jmjm="
      "8,ckm=4,fv-,sp-,jsm=7,rtm-,ph=4,txx=8,vtlv-,fv=3,sr=5,gx=7,dq-,rp=4,"
      "qbfzcq-,hqkg=1,vhtd=3,vm=4,kg-,sq=4,bvj=8,lls=8,qvccp-,ttj=7,dbh=8,qbx-,"
      "kq-,rg=9,ccvd-,qstfm-,dttz=5,vh-,dfpx-,bls=9,dqsq-,kbg=9,zprzq-,rc=4,"
      "gtzk=5,bvd-,pdlz-,pp-,zvc=8,mnz=3,cf-,mng=1,zx-,bgt=1,ntn=8,mnz-,cpqh-,"
      "pjb=3,th=2,ltvf-,bl=6,lq=6,jpb=7,pch=1,gbx=9,hgnr=5,gg-,jbh=6,xmprb-,"
      "gxh-,zdc-,tppcb=9,mt-,zq-,lrf-,tqjb=1,bz-,kfdb-,llg=8,jb=5,cjx-,nn-,gz-,"
      "vcm-,czt-,zvc-,pctvf=8,jjlrr-,pzxc-,trjtl-,cn-,vtlv=8,qvs-,qsm-,vdm=1,"
      "vdj-,pqdl-,tq-,lqv=9,rcrfs=6,df-,qcfz=4,vqp-,qvs=2,ltj-,hb=4,sxj=6,xrt-,"
      "hb=1,vzd=7,jt-,qhgf=5,vqq-,hcqh=8,rq=8,hhtb=8,th=9,chdk-,sbvx=3,xxk=7,"
      "ttj-,cgv=2,vmf=6,xgqj=4,lq=3,tq-,bvj-,mx-,px-,tz-,bnf=3,jzl-,slb=7,vtlv="
      "9,cmq=5,kbg=1,kfdb=8,lfpjzc-,nrsgfn-,rktk-,kjxx-,xxk-,chdk-,lg-,fr-,mjt="
      "3,rhlv-,slb=7,jzl-,gtkl-,zkpz=5,mmx-,vtlv-,kfp=9,zfsz=7,zdtkk-,vqq=9,"
      "ktskt=2,mzr=8,cjx-,dfsb=2,rzkc=1,lrhgd=7,qklv-,ptpr=1,cbp-,qklv-,msrgsb="
      "3,kdplr=1,kg=7,rdl=5,chdk=9,xg=8,qj=5,srr-,lls-,qcfz-,qpllk-,mv=2,lq-,"
      "dz-,sdhl-,jllf=8,lztjd-,cxmp=5,zp-,qk=5,cmq-,blllmg=7,sc=7,rhlv-,mp=6,"
      "lz=7,cb-,xpm-,zdnd-,trhc=4,bsl=6,mp=1,tsz-,gvh-,ggvcqj-,bl-,pqdl=2,bl=4,"
      "cb-,tn-,ktt=1,fdz-,fr-,dq=9,gxh=8,qpllk=8,pjc=6,qpllk=6,tqcxq-,mzr=2,dp="
      "6,mjt-,cx-,ldd=2,xrf-,vvh-,tflk-,sgklt=9,vm=6,qk=8,cj=8,gft=1,dqr-,"
      "gjmjrv-,hn=3,ds=1,zc=6,ldc=1,tc=3,vmf=7,mng-,nzl=7,xrt=3,sp=3,dxr=2,lqv="
      "8,zsn-,xg-,xrt=9,mjt=1,qk=4,cbf=4,tppcb-,lnh=8,znc=4,qn=3,tj=6,bf=8,dqj-"
      ",rqr=8,chdk-,fhv=7,gxh-,vdm=6,zbmts=8,qdgm=2,zkpz-,zzq=2,qsm=5,jb-,gr-,"
      "vmf-,ldc-,hqkg-,vrv=5,ft=2,vvtdp-,kxg=7,cbp-,cj=1,kt-,rc-,xk=1,zv-,rsbz-"
      ",lztjd=7,lqn-,tp=3,vcm=7,ztqc=2,vfdlhq-,kfdb=9,bs=4,vvkcff-,zsn-,tpg-,"
      "mnz=2,gqh=2,hd-,hjc=4,vhtd=7,bgt-,dxblpb=7,frvv=6,jzl=9,mrb=1,kdplr-,"
      "qmlf-,gjz=5,pz-,fttkg-,qpllk-,bl-,gvk=2,hz=5,psmm-,hzst=1,bz-,dqsq=7,"
      "dhs-,ltj-,vh-,trhc-,ht=6,rzkc=2,cmk-,gttk=1,xlhxd=4,cx-,nks-,zfsz-,nvc-,"
      "bz=6,slb-,jllf=2,rg-,dz=6,jqk=5,zstl-,tlk=7,hs=6,sf=8,vqq-,cjd-,lm-,sq-,"
      "pq=3,px-,cntk=7,njn=4,xgcpp=6,vj-,ldd=5,nvc-,xgqj=7,rcm-,gtzk=1,zfsz-,"
      "mc-,gb=8,jcxr-,tlk=8,zbmts-,cnr-,qds-,zfsz=2,ptpr=2,vj=5,qhgf-,jz-,nvj="
      "2,cnb-,qdgm-,dm-,vkz=8,rsmvds-,fr=9,qdk-,fdz-,xt-,rsbz-,rsmvds-,lpchk=3,"
      "tlk=9,gq=8,qsm=3,zbmts-,hk-,vhtd-,rp-,qpllk-,llqt-,tbspnx=2,nxtt=2,"
      "zdtkk-,ktt-,psh-,vgfr-,zbmts-,sf-,tss-,lqn-,kgn=2,mstnpg-,rjtl=7,zvtkxm-"
      ",xv-,qdgm=6,vl-,xmprb-,hzst=9,njn-,dqdv-,cgv=7,vv=8,zprzq=1,qct=5,zkpz-,"
      "tqjb=4,lgp=3,jmf=4,kz-,cn=4,hzst-,bz=4,kfdb=6,pz-,lnh-,slb=7,pk=7,np-,"
      "nrnx=8,nxtt-,tsz-,fhv=1,fpxz=4,jt=1,bgt=3,hz-,zsb-,hjc=4,gnh-,vj=8,vd=7,"
      "qt=6,kcp=8,dfpx=5,gqg-,bls-,bs-,nr-,xmprb-,mkc-,vj-,vh=3,kfdb-,vt=6,"
      "bvpqdj-,lrhpc=2,qh=8,scg-,mlkg-,lpchk-,vtb=8,jjqmb-,mtr=4,bnf-,ggvcqj=1,"
      "sjn=3,mm=4,rdl-,dm-,tlk-,cj=6,dp=1,cmk-,pdk=5,dpfnqr-,gfcql=2,rpp-,"
      "gjmjrv-,kdplr-,hcqh=2,bgt=6,jvd-,mzr-,dttz-,kz-,mxg=8,xm=7,vgfr-,tc-,hn-"
      ",qq=3,mpg-,ptpr=1,zdnd-,xn=2,stv-,rpp=6,ccvd=5,nxtt-,gjdbf=9,tjl-,hn=6,"
      "pz-,pjc-,nvf-,jgpjxb-,bxc=6,psmm-,dl=8,gfcql=2,ds=8,pctvf-,mg-,qh-,fdz="
      "9,rdl=4,qdq=9,nvc-,dqj=1,nn=9,vvkcff=8,gm=9,sb-,rng-,sf=9,xg=5,tbspnx=7,"
      "hqkg-,kfdb-,gg=2,pdk=5,rcl-,pzxc=6,tmn-,zsn-,mstnpg-,ql-,qt=1,gt=5,"
      "qstfm-,cclj=9,ql=5,xgcpp-,vrv=6,lfz=4,gbb=3,kdplr-,tcv=5,jkm-,qh-,gl-,"
      "xg-,pp=9,gq=7,vtlv=1,qrprpd=3,zprzq-,bls=5,vmkb=2,sr=5,mmx-,tp-,fgrngv-,"
      "ngmd=5,xg=4,szp=7,rzkc-,xznps-,xms=8,xrf=5,dqsq=5,bnf-,psh-,gft=6,gbx-,"
      "lffflt=2,tq=9,sqkc=7,dm=2,cjd=4,mt=8,qbx-,ckm-,db=2,pdk=6,qdq-,tppcb-,"
      "ckm=5,rcm=5,fhb-,lx=1,mm-,sks=3,qt-,vzldq=7,qhnr=9,xr-,ntpn-,sv-,gkbl=7,"
      "pq=1,kgn-,njc=7,lz=1,fpxz=5,mjt-,hs=2,kv-,rb-,cbp-,tbspnx-,hjc=4,qdk=8,"
      "fv-,vtng=5,hgnr-,bvd=3,zstl=7,nkqs=6,ngmd=5,vt-,bvd-,pp=6,phr=8,gft-,mx-"
      ",cgv-,xpm-,sp-,qxp-,tsz=6,xkx=2,zkpz-,tbspnx=1,vgfr-,zr-,cb=2,dz=9,th=6,"
      "lrhgd=9,lq-,zsb=3,lfpjzc-,rj-,mrrj-,qds-,ctf-,kn-,vtng=5,tl-,pgx=5,lls="
      "7,vpd-,dxz=7,zstl-,hqbmx=8,kgn=4,cpq-,rj-,gvk-,ntn=7,tqcxq=1,vtlv-,dttz="
      "2,xxk=6,tvjb=4,fttkg=1,kv=8,trhc=1,zq-,hhtb=5,stv=5,xxk-,vmf-,lqv-,xr=1,"
      "vv=9,zdtkk=2,bls=9,lq-,qk=6,ft=9,gjz-,zp-,hbbl=7,lrhpc-,vkm=1,gfcql-,cn="
      "2,rqr-,mrb=5,trhc-,xhbs=3,xxk=5,cpqh=6,xbx-,mzt-,bsl-,hd=8,hb=4,tj=1,"
      "lpchk=4,rms=9,djd=9,jmf-,hdf=7,mqg-,mp=9,tflk=8,pch=1,sbvx=2,jcxr=1,dxz="
      "8,ts=6,xg=6,xg-,th-,rp=6,nr=7,jqk=3,zdnd-,vtng=6,rzkc-,cbf-,cs-,ztqc=1,"
      "jvd-,vd-,mchc-,gb=4,gg-,dqsq-,dttz-,vd=7,tl=5,bs-,qhg=8,dzd=1,cf=7,"
      "nrhbm-,rp-,dbh=7,gbb-,hqcqb=7,vv=7,tss-,cpq=5,xgcpp-,jb-,df=6,cx-,gjz=5,"
      "lqn=2,ttj-,ntn-,pp-,fgb-,sjlk=5,sgl-,ltvf-,vh=9,gq-,pz=1,mfb-,mh=9,nr=8,"
      "vtng-,hdf=4,vdm=5,jsr=7,qhgf-,mzp-,cl=3,tvjb=3,kt=2,tsz=5,mrb=3,txx=2,"
      "qstfm-,xpm-,pmd=3,dbh-,zvtkxm=6,lj-,mrrj=8,gg=5,cmk-,cn-,mv-,trbd=2,jz="
      "5,tz=3,rkr-,xms=9,qqzt-,rcrfs-,llg=7,lq-,sqkc-,trjtl-,jpb=2,gb-,cxmp-,"
      "fcn-,kg-,vkm=4,lrhpc-,vrv-,bp=8,llqt=1,tflk=2,gvh=6,zc=7,nkqs-,trjtl-,"
      "vvtdp=3,znc-,dt=5,pp=5,gtkl-,dct-,qdk=1,pp=5,hzm=6,ctf=6,rsmvds-,llg-,"
      "gkbl=8,nvf=4,czt=2,gt=9,vvkcff-,zr=1,db-,xn=6,vdj=7,vm-,slb=9,xhbs-,gm="
      "1,rb=2,dr=6,ds=5,ts=9,mh=8,gz-,xrf=6,vrv=8,fr=8,tb=9,bls=7,gm-,sqkc=8,"
      "njn-,sks-,sf=2,gqh=4,nkqs-,mfb-,pxpr-,psmm=3,qvs-,cnb-,kcp-,rzkc-,hqbmx-"
      ",ct=5,jsr-,jb=7,ql=1,mzr=5,dgs-,gtcgmx=3,dgs-,pdlz=9,slb=2,pc-,nvj=8,"
      "qds=4,bs=9,tr-,vpd-,cdgvf=2,xqdtf=5,gm=1,jz=5,psh=8,ccvd=2,sc-,hd-,"
      "gtcgmx-,qdq-,ngxq-,xf=5,gtzk-,jkm=3,bnf=2,gl=6,zbzv-,vj-,kd-,bls-,bgt-,"
      "jzl=1,cf-,ngxq=8,cnb=3,sjlk-,mzp=7,ql=1,bd-,rq=5,cj=4,xqdtf-,vtln-,tcv-,"
      "qqzt=8,fcn=1,bsgjn-,qdgm=5,bgt-,ktt=3,lx-,xrt=8,cnr=6,xpm-,tjl=3,nks=7,"
      "kkrnf-,jz-,tz=7,dqsq-,xhbs=3,df=7,tqcxq=6,hz-,rjtl=6,qx-,xk=7,pd=4,gvh-,"
      "fpxz-,xmprb=8,lztjd=2,lztjd-,tc=1,hlk=7,tsz=5,pxpr-,qct-,qcfz=2,pv=8,rc="
      "6,vvh=8,zsb-,pmd=4,kjxx=4,qx-,rcm-,ts=6,dgs=7,zzq-,qbm=9,ngmd=9,dm-,mrb="
      "3,mtr-,fttkg-,bkl-,gkbl-,dkc-,hzst=6,lqn=9,kblbg-,jd=2,fd-,bxc=3,vh-,sr-"
      ",mxg=8,bsg=2,fcn-,vpvjp=3,qvnq=3,zzq-,ts-,njn-,mknpz-,vqp-,bf=2,qj=8,zv-"
      ",btdxxp=8,scg-,kblbg-,ts-,zbzv-,sjn-,tz=5,jgpjxb=2,ltj=7,sf=2,zsn-,"
      "fttkg=8,gxh=4,qqzt=5,hnzjq-,qstfm-,ncft-,gt=6,pxpr=3,mpg-,sr-,tj=1,np=3,"
      "nqcfs-,hsxn-,rq-,lrhpc=5,hbl=8,xm-,cjx-,cx=9,tss-,tqjb=9,fttkg=8,ktskt="
      "4,kn-,gvh=7,pdk=2,cnr-,sr=4,vdj-,vdm=2,xhbs=5,pp-,zsbj-,vtlv=6,mlkg-,"
      "mknpz=6,vhtd-,vvh-,kqgq=9,tvjb=1,ngmd-,vmf=7,mng-,gnh-,kblbg-,hqkg=4,"
      "mrrj-,qds=2,dx-,qklv-,nn=2,hkjk-,dbh=6,cdk-,zjn-,rsmvds-,zq-,ztqc-,qvnq-"
      ",vdm=8,rktk-,rg-,hhtb=7,tj-,cdk=2,mnz=7,vzldq-,zdnd-,gg-,gm=7,mqg=8,hlk="
      "7,rpp=9,msrgsb=3,xr=5,zx-,zprzq=2,qdk=9,fdz-,tl-,qdk-,mzp=3,bp-,pzxc=4,"
      "cs=1,bs-,tlk-,nvc=6,lqn-,tpg=7,jvd=4,gt=2,trhc=6,sr=8,czt-,sjn-,fcn=6,"
      "vpd-,mng=9,kdplr=7,dxz-,sjlk=1,ql=3,tlk-,zvc-,cgv=5,lrhgd-,hdf=6,lx=7,"
      "jmjm=8,sgl=5,gqh-,czt-,bsl=1,gz-,jbh-,qqzt=6,gfcql=5,cx=7,sxj-,cnb=8,"
      "rqr=6,ct-,vcm=1,jsm=7,cx=6,qxp-,ltj=7,sv-,jzl=6,qhnr=5,zprzq=2,dxhg-,hb="
      "6,gr-,sdhl-,phr-,bsl-,vzd-,gjdbf=6,nvc=4,fp-,btdxxp=5,qk=2,lqn-,lrhpc-,"
      "kjxx=6,qhg-,nvsr-,zbmts-,gh=7,qcqt-,zjn-,bx=7,ss-,ts=2,lfz-,kp-,bx-,ldc="
      "7,qbm-,ptpr-,tn=6,ps-,zjn-,dqdv=3,gbx=7,frp=1,hs=1,vt-,vjvm=6,gjdbf-,"
      "lztjd-,nvf=4,qdq-,phr-,lj=8,dttz-,qrprpd=3,llg-,dgcgc=6,kd-,fd-,hzm-,"
      "dxblpb=9,gdt=6,slb-,vt-,gtzk-,zv-,qsm=7,zccc-,vcm=4,sqkc-,mfb-,kqgq=3,"
      "kjxx=1,rmh=6,bsgjn=8,srr-,dl-,mfb-,zgb-,gtkl=9,trhc-,zstl=2,jmf-,gq=9,"
      "rb=4,cl-,cbf=6,bx-,jzl-,hgf=8,mrrj=2,vvh=7,zvc-,qhnr-,hqcqb-,nvc=2,stv-,"
      "scg-,kfdb=8,xqdtf=1,dxhg-,llqt=2,tpg=8,lfpjzc-,sqkc-,gqh-,dbh=2,nr=7,dr="
      "1,qcqt=1,hfcm-,vtng=1,znc-,vhtd-,nlxbzc-,qdq-,dcdrv-,vzldq-,gqg-,rsbz-,"
      "tlk-,qsm=8,dbh-,nkqs-,czt-,pdlz=5,tsz-,trbd-,qsm=6,hn-,sr=6,rpp-,bn=8,"
      "zkpz=1,vzldq-,kblbg=4,hd-,hzm-,dll=4,pkr=9,qt=4,tcv-,dcdrv=9,ft=2,kgn=1,"
      "dxblpb=2,dq-,qrprpd=9,xv=3,gtzk=2,vv=6,vh-,hkjk=8,cxmp=2,lm=7,gl=8,mv-,"
      "hgf=2,kq=5,kqnjk-,dx=2,lgp-,vgfr-,gqg-,klc-,cntk-,pbpxf-,szp-,tppcb-,"
      "vvkcff=8,qbx-,nxtt-,fv=9,vm=3,cx-,psh-,fhb-,vtln-,cn=2,qt-,gtzk=5,tj-,"
      "mg-,tppcb-,vgfr-,ql=5,nr=6,hd=4,dp-,tflk=3,cj-,qdq=5,gtcgmx=8,dpfnqr-,"
      "qbx-,tmn=5,hzm-,ldd-,qx=9,pc=2,ktskt=4,kfdb-,nff-,nq-,kqgq=7,qbx-,qq=2,"
      "ldc=1,rmh=8,pkr-,ztt-,qq-,qqzt-,zbzv-,pk=8,vmf-,tz=1,hlk-,mh-,lfz-,"
      "gtcgmx-,qdk-,pxpr-,zsgct=6,sgl=6,cd=8,jllf=9,fgrngv-,qdgm-,zhc-,qdk=4,"
      "pjc-,cdk-,ct=3,dcdrv=4,sgl-,hzst=3,jvd-,svcb-,gvk=2,bvd=2,ncft=7,gx=4,"
      "njc=7,rmh=4,ntpn=5,tqjb-,gtcgmx=4,rkr=8,xk-,zbzv=5,qds-,rkr-,xk-,cnb-,"
      "dq=8,vpd=6,fcn=1,dl=6,xv=2,qpllk-,pzxc-,pz=7,ldc=4,tmn-,qstfm-,kjxx-,qq="
      "8,pqdl=5,qstfm-,vpd=6,ztt=8,ht-,pm-,xms=9,zsb-,nvsr-,fpxz=3,djd=6,kt=6,"
      "nkqs=4,rcm-,dzd=2,nq=8,sb-,rzkc=1,zsb=5,pp=7,ztqc-,bnf-,rqr=1,xn-,"
      "jgpjxb-,jsm=8,qhg=4,rsbz=9,qhgf-,rpp-,gq=8,pp-,tfm-,lz=9,mv-,xbx-,lfz=4,"
      "mmx-,hlk-,ktskt=6,bvd=6,mm=8,rms=7,pp-,mm-,hbbl=2,bx=4,ntn-,qjzk-,jqk-,"
      "jsr=6,qqzt=3,hnsghx=5,ztqc=7,pp-,rc=3,sp-,ltj-,bf-,cl-,sp=9,jzl-,qcqt=5,"
      "qvnq-,qpllk=3,mrrj-,xgqj-,rqr-,dgcgc=5,ccvd-,dl=8,msrgsb-,kgn=9,mv-,nvj-"
      ",fdz=6,ljg=8,vm-,trhc-,njc-,vgfr=6,dcdrv-,cxzq=2,ntpn=2,mknpz-,cxzq-,"
      "pdk-,zprzq-,kqnjk=6,txx-,pv=4,rhlv-,frm=9,gqg-,gh=2,lx=5,tn=4,srr-,trhc="
      "8,bp-,kblbg=8,lkl=7,zbzv=2,gttk-,mstnpg=9,rcrfs=9,jjlrr-,hnsghx=5,xqdtf="
      "3,gtcgmx=1,gkbl-,ngxq-,zkpz-,vc-,gh-,zprzq=6,szp-,xk=4,blllmg-,gl=5,mpg="
      "1,bbl-,nq-,kdplr-,btdxxp=5,msrgsb-,nqcfs-,zp-,dx-,dm=3,jmjm-,vvkcff=9,"
      "mz-,gb=8,fd-,bls=8,dx-,fp=4,sbvx=4,ph-,hsxn=6,ctf-,tppcb=4,lfz-,bs=3,"
      "lpchk-,nvc-,kqbt=1,ngmd=6,cbp-,llqt=5,hgnr-,dll-,gl=3,pp=6,ht=4,nvf-,"
      "rcrfs-,gm-,vh-";
  std::vector<std::string> steps = split(input, ',');
  std::array<std::list<std::pair<std::string, int>>, 256> boxes{};

  for (auto const& input_step : steps) {
    step_t step = parse_step(input_step);
    int box_num = hash(step.label);
    if (step.op == '-') {
      std::list<std::pair<std::string, int>>& box = boxes.at(box_num);
      box.remove_if([step](auto& a) { return a.first == step.label; });
    } else {
      std::list<std::pair<std::string, int>>& box = boxes.at(box_num);
      auto it = std::find_if(box.begin(), box.end(),
                             [step](auto a) { return a.first == step.label; });
      if (it != box.end()) {
        it->second = step.focal_len;
      } else {
        box.push_back({step.label, step.focal_len});
      }
    }
  }

  int total = 0;
  for (int i = 0; i < boxes.size(); i++) {
    int j = 1;
    for (auto const& [label, focal_len] : boxes.at(i)) {
      total += ((i + 1) * (j) * (focal_len));
      j++;
    }
  }

  std::cout << total << '\n';
}