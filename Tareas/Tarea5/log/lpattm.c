// (c) Michael Buro 1992-2002, licensed under the GNU Public License, version 2

// pattern test with list / 1.97

#include "main.h" 
#include "board.h"
#include "crt.h"
#include "patt.h"
#include "fpatt.h"
#include "eval.h"
#include "trans.h"

#define TEST		false
#define ECKEN		false

#define WRITE_VEC       true
#define VALUE_TEST      false

#define VAL_NUM		10000


#define OUT_NUM         (54)
#define SAVE_PERC       0.01

#undef X

int f_aus=false;


typedef struct {

  int   index, z;
  int   n;
  float y;

} ENTRY;


typedef struct {

  int  num;
  int  *values;

} VALUES;


#define MAXLEN	16

typedef struct {

  int   sq[100];
  int   perm[MAXLEN+1];
  int   l;
  int   list_len;
  ENTRY *list;
  int   sqlist[MAXLEN+1];

  VALUES Val0[INUM], Val1[INUM];

} PATTERN;



#define PATTNUM	1


PATTERN Patterns[PATTNUM] = {

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  /*
  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,2,3,0,0,0,0,0,0,
      0,4,5,0,0,0,0,0,0,0,
      0,6,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }, true, {1,4,6,2,5,3}}

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,0,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}
  */
  /* 

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,1,1,0,
      0,1,1,1,1,1,1,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,1,1,1,0,
      0,1,0,0,0,0,0,1,1,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},
  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}

     

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,1,1,1,0,
      0,0,1,1,1,1,1,1,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},



  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,1,1,1,0,
      0,0,1,0,0,0,0,1,1,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},
,

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}
     

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,1,1,1,0, 
      0,1,1,0,0,0,0,1,0,0, 
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,1,1,1,0, 
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}


  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,1,1,1,0,
      0,1,0,0,0,0,0,1,1,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,1,1,0,
      0,1,1,1,1,1,1,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}
  */

};


void _abort(void) { exit(1); }




void StrahlAus(FILE *fp, int n, int SteinAnz)
{
  int i, r;


  FOR (i, SteinAnz) {

    r = n % 3;
    
    if      (r == 0) SteinEinfAus(fp, WHITE);
    else if (r == 1) SteinEinfAus(fp, LEER);
    else             SteinEinfAus(fp, BLACK);

    n /= 3;
  }

}
  

void InitPattern(PATTERN *pPat)
{
  int i, num=0;

  FOR (i, 100) {

    if (pPat->sq[i]) { 

      if (!ZUG(i)) Error("edge square in pattern!");

      if (num >= MAXLEN) Error("too many squares!");
      pPat->sqlist[num++] = i;
    }
  }

  if (!num) Error("no squares!");
  pPat->sqlist[num] = 0;


  if (!(pPat->list=(ENTRY*)calloc(sizeof(ENTRY), MAX_LIST_LEN))) 
    Error("no memory");

  pPat->list_len = 0;
  pPat->l = num;

  FOR (i, INUM) {

    pPat->Val0[i].num = 0;
    pPat->Val0[i].values = (int*) malloc(VAL_NUM * sizeof(int));
    if (!pPat->Val0[i].values) Error("no mem");

    pPat->Val1[i].num = 0;
    pPat->Val1[i].values = (int*) malloc(VAL_NUM * sizeof(int));
    if (!pPat->Val1[i].values) Error("no mem");

  }
}


int Pattern2Index(sint1 *p, PATTERN *pPat)
{
  int i, s=0;

  FOR (i, pPat->l) {

    s = s + s + s + p[pPat->sqlist[i]];
  }
  return s + (Pot3[pPat->l]-1)/2; 
}



void Index2List(int s, int len, int *List)
{
  int i;

  FOR (i, len) {

    List[len-1-i] = s % 3 - 1;
    s /= 3;
  }
}


void fShowPattern(FILE *fp, PATTERN *pPat, int s)
{
  int x, y, num=0, List[MAXLEN+1];

  Index2List(s, pPat->l, List);

  FOR (y, 8) {

    FOR (x, 8) {

      if (pPat->sq[Tab8to10[(y << 3) + x]])
	SteinEinfAus(fp, List[num++]);
      else 
	fprintf(fp, ":");
    }
    fprintf(fp, "\n");     
  }
}



void Ratios(PATTERN *pPat)
{
  int  i, j, anz, StrahlAnz, SteinAnz=pPat->l;
  ENTRY *list=pPat->list;

  FOR (i, pPat->list_len) {

    list[i].y[j] /= (list[i].n[j] + 0.0001);

  }
}



// return index of pattern configuration x in list

int SearchConfig(PATTERN *pPat, int x)
{
  int l=0, r=pPat->list_len;

  FOREVER {

    



  }
}




// output 

void WritePatt(char *name, PATTERN *pPat) 
{
  int  i, j, anz, StrahlAnz, SteinAnz=pPat->l;
  FILE *fp;
  ENTRY *tab=pPat->tab;

  fp = fopen(name, "w");
  if (!fp) Error("Schreibfehler");
 
  StrahlAnz = Pot3[SteinAnz];

  anz = 0;

  FOR (i, StrahlAnz) {

    fShowPattern(fp, pPat, i);
    FOR (j, INUM) { 
      fprintf(fp, "%2d: %.1f %d\n", I0+j*IWIDTH, tab[i].y[j], tab[i].n[j]);
    }
  }
  
  fprintf(fp, "\nNumber: %d\n\n", anz); fclose(fp);

}

static int compREAL(const void *a, const void *b)
{
  REAL r;

  r = *(REAL*)a - *(REAL*)b;

  if       (r < 0.0) return -1;
  else if  (r > 0.0) return  1;
  else               return  0;
}


static int compLONG(const void *a, const void *b)
{
  return *(long*)a - *(long*)b;
}

 

REAL discord(VALUES *pVal0, VALUES *pVal1)
{
  int i, j, num01, num0=pVal0->num, num1=pVal1->num;
  long *AllVal;
  long long su, anz;


  num01 = num0 + num1;

  if (!num0 || !num1) { printf("\a"); fflush(stdout); return 0; }


  AllVal = (long*) malloc(num01 * sizeof(long));

  if (!AllVal) Error("no mem");

  FOR (i, num0) AllVal[i]      = pVal0->values[i];
  FOR (i, num1) AllVal[i+num0] = pVal1->values[i];


  qsort(pVal0->values, (size_t) num0,  sizeof(long), compLONG);
  qsort(pVal1->values, (size_t) num1,  sizeof(long), compLONG);
  qsort(AllVal,        (size_t) num01, sizeof(long), compLONG);


/* count pairs with val1 > val2 but cl1=loss and cl2 = win */

  su = 0; i = 0;

  FOR (j, num0) {

    while (i < num1 && pVal0->values[j] >= pVal1->values[i]) i++;

    su += i;
  }


#if 0

/* count pairs with val1 < val2 */ 

  anz = j = 0;
    
  FOR (i, num01-1) {

/* printf("%d %d %d %d\n", i, j, num01, pK01->dimy); */

    j = i+1;

    if (j < num01 && AllVal[i] == AllVal[j]) j++;

    anz += num01 - j; 

  }

#endif

/*??? num0/num1??? */
  anz = (num01*(num01-1))/2;


  free((char*)AllVal);

  return ((REAL) su) / anz;
}



int main(int argc, char **argv)
{
  char name[100];
  int  i, j, k, l, s, ind, Marke, dateinr, StrNr, Anz, 
       num[INUM], num0[INUM], num1[INUM], *pnum;
  int  AnzG=0, AnzV=0, AnzR=0;
  uint4 z=1;
  SPFELD sf;
  FILE  *fp;
//  bool f_r=false;
  float Wert, PattVal[PATTNUM];
  int   PattErr[PATTNUM][INUM];
  VALUES *pVal;



  InitCrt();
  InitSetzen();


  if (argc != 3) {
    Error("call: opatt estimate-sfk-file check-sfk-file");
  }

  StrNr = 1;


  FOR (i, PATTNUM) InitPattern(&Patterns[i]);

  FOR (i, FEATURENUM) InitFeature(i);


  FOR (i, PATTNUM) {

    printf("%d: \n", i);

    FOR (j, 8) {

      printf("  STRAHL%d(+,", Patterns[i].l);

      FOR (k, Patterns[i].l) { 
	KoorAus(Trans[j](Patterns[i].sqlist[k])); printf(",");
      }
      printf(");\n");
    }
    printf("\n");
  }



#if VALUE_TEST
  goto value_test;
#endif

/********************** estimate tables ************************/


  { 
    int index, indices[8];

    sprintf(name, "%s", argv[StrNr]);
  
    printf("opatt: %s\n", name);

    fp = fopen(name, "r");

    if (!fp) { Error("can't open file\n"); }


    for (i=0; ; i++) {

      j = fSfRead(fp, &sf, 1);

      if (j != 1) break;
 
      Marke = sf.Marke;

      Wert = 0.0;

      if (Marke == MA_WEISS_NICHT) { printf("position not classified"); continue; }

      if      (Marke == MA_GEWONNEN) { Wert = +127; AnzG++; }
      else if (Marke == MA_VERLOREN) { Wert = -127; AnzV++; }
      else if (Marke == MA_REMIS)    { Wert = 0;    AnzR++; }
      else if (Marke >= MA_WKEIT && Marke <= MA_WKEIT+100) {

	if (Marke >  MA_WKEIT+50) AnzG++; 
	if (Marke <  MA_WKEIT+50) AnzV++; 
	if (Marke == MA_WKEIT+50) AnzR++; 

	Wert = (Marke - MA_WKEIT - 50) * 127.0 / 50.0;

      } else if (Marke >= MA_DIFF && Marke <= MA_DIFF+128) {

	if (Marke >  MA_DIFF+64) AnzG++; 
	if (Marke <  MA_DIFF+64) AnzV++; 
	if (Marke == MA_DIFF+64) AnzR++; 

	Wert = (Marke - MA_DIFF - 64) * 127.0 / 64.0;

      } else { Error("unknown label"); }

      if (Wert == 0) continue;  // no draws

      Anz = SfAnz(&sf);

      ind = (Anz - I0) / IWIDTH;

      if (ind < 0)      ind = 0;
      if (ind > INUM-1) ind = INUM-1;

      z++;

      if (!(z & 4095)) { printf("%8lu\r", z); fflush(stdout); }

      if (z > 1000000000) Error("too many positions\n");

#if FEATURENUM > 0

      { BRETT br;

	SfBrett(&sf, &br);

	FOR (i, FEATURENUM) {
          features[i].means[ind] += features[i].func(&br);
          features[i].n[ind]++;
	}

      }

#endif

      index = 0;

      FOR (k, 2) {

	FOR (j, 4) {

	  FOR (l, PATTNUM) {

 	    s = Pattern2Index(sf.p, &Patterns[l]);

	    if (s < 0 || s >= Pot3[Patterns[l].l]) Error("s");

/*printf("%d %d %d\n" , l, s, Pot3[Patterns[l].l]); */

	    if (Patterns[l].tab[s].z != z) {
		
	      Patterns[l].tab[s].z = z;	        
	      Patterns[l].tab[s].y[ind] += Wert;
	      Patterns[l].tab[s].n[ind]++;

/*printf("%d %f %d\n" , s, Patterns[l].tab[s].y[ind], Patterns[l].tab[s].n[ind]); */

	    }
	  } 

	  index++;

	  SfDrehen(&sf);
	}

	SfTransponieren(&sf);
      }

    }

    fclose(fp);
  }
      
  printf("opatt: %d won, %d drawn, %d lost\n", AnzG, AnzR, AnzV);

  FOR (i, PATTNUM) Ratios(&Patterns[i]);

#if FEATURENUM > 0

  FOR (i, FEATURENUM) 
    FOR (j, INUM) features[i].means[j] /= features[i].n[j];

#endif

#if WRITE_VEC

/*************** write vectors **********************/

  { 
    int index, indices[8];

    printf("# vectors\n");
    
    FOR (k, Pot3[Patterns[0].l]) {

      if (Patterns[0].tab[k].n[1] > 0 && k <= Patterns[0].tab[k].sym_ind) {
	printf("# %d\n", k);
      }
    }

    printf("#\n");

    
    sprintf(name, "%s", argv[StrNr]);
  

    fp = fopen(name, "r");

    if (!fp) { Error("can't open file\n"); }


    for (i=0; ; i++) {

      j = fSfRead(fp, &sf, 1);

      if (j != 1) break;
 
      Marke = sf.Marke;

      Wert = 0.0;

      if (Marke == MA_WEISS_NICHT) { printf("position not classified"); continue; }

      if      (Marke == MA_GEWONNEN) { Wert = +127; AnzG++; }
      else if (Marke == MA_VERLOREN) { Wert = -127; AnzV++; }
      else if (Marke == MA_REMIS)    { Wert = 0;    AnzR++; }
      else if (Marke >= MA_WKEIT && Marke <= MA_WKEIT+100) {

	if (Marke >  MA_WKEIT+50) AnzG++; 
	if (Marke <  MA_WKEIT+50) AnzV++; 
	if (Marke == MA_WKEIT+50) AnzR++; 

	Wert = (Marke - MA_WKEIT - 50) * 127.0 / 50.0;

      } else if (Marke >= MA_DIFF && Marke <= MA_DIFF+128) {

	if (Marke >  MA_DIFF+64) AnzG++; 
	if (Marke <  MA_DIFF+64) AnzV++; 
	if (Marke == MA_DIFF+64) AnzR++; 

	Wert = (Marke - MA_DIFF - 64) * 127.0 / 64.0;

      } else { Error("unknown label"); }

      if (Wert == 0) continue;  // no draws

      Anz = SfAnz(&sf);

      ind = (Anz - I0) / IWIDTH;

      if (ind < 0)      ind = 0;
      if (ind > INUM-1) ind = INUM-1;

      z++;


#if FEATURENUM > 0

      { BRETT br;

	SfBrett(&sf, &br);

	FOR (i, FEATURENUM) {
          features[i].means[ind] += features[i].func(&br);
	  //          features[i].n[ind]++;
	}

      }

#endif

      index = 0;

      FOR (k, 2) {

	FOR (j, 4) {

 	  s = Pattern2Index(sf.p, &Patterns[0]);
	  
	  if (s > Patterns[0].tab[s].sym_ind)
	    s = Patterns[0].tab[s].sym_ind;
	    
	  indices[index++] = s;

	  SfDrehen(&sf);
	}

	SfTransponieren(&sf);
      }

      if (index != 8) Error("index?");

      if      (Wert > 0.1)  printf("99");
      else if (Wert < -0.1) printf(" 1");
      else                  printf("50");

      printf(" 100 ");

      FOR (k, Pot3[Patterns[0].l]) {

	if (Patterns[0].tab[k].n[1] > 0 && k <= Patterns[0].tab[k].sym_ind) {

	  int sum = 0;
	  FOR (l, 8) if (indices[l] == k) sum++;

	  printf("%d ", sum);
	}
      }

      puts("");
	
    }

    fclose(fp);
  }

#endif

/*************** calculate errors **********************/


  FOR (l, INUM) {

    FOR (k, PATTNUM) PattErr[k][l] = 0;

  }

  FOR (i, INUM) num[i] = num0[i] = num1[i] = 0;


  FOR (k, PATTNUM) {

    char name[100];
    sprintf(name, "str%d", k);
    printf("opatt: %s\n", name);
    WritePatt(name, &Patterns[k]);

  }



#if VALUE_TEST

value_test:

  // load pattern values


  fp = fopen("values", "r");

  if (!fp) { Error("can't open values\n"); }

  FOREVER {

    float v;
    int i;

    if (fscanf(fp, "%d %f", &i, &v) != 2) break;
    
    Patterns[0].tab[i].y[1] = v;

  }

  FOR (k, Pot3[Patterns[0].l]) {

    if (k > Patterns[0].tab[k].sym_ind) 
      Patterns[0].tab[k].y[1] = 
	Patterns[0].tab[Patterns[0].tab[k].sym_ind].y[1];

    printf("%d %f\n", k, Patterns[0].tab[k].y[1]);
  }

  fclose(fp);

#endif











  {
    sprintf(name, "%s", argv[StrNr+1]);
 
    printf("opatt: check %s\n", name);

    fp = fopen(name, "r");

    if (!fp) { Error("can't open file\n"); }

    z = 0;

    for (i=0; ; i++) {

      j = fSfRead(fp, &sf, 1);

      if (j != 1) break;

      z++;

      //      if (!(z & 4095)) { printf("%8lu\r", z); fflush(stdout); }

 
      Marke = sf.Marke;

      Wert = 0.0;

      if (Marke == MA_WEISS_NICHT) Error("position not classified");

      if      (Marke == MA_GEWONNEN) { Wert = +127; AnzG++; }
      else if (Marke == MA_VERLOREN) { Wert = -127; AnzV++; }
      else if (Marke == MA_REMIS)    { Wert = 0;    AnzR++; }
      else if (Marke >= MA_WKEIT && Marke <= MA_WKEIT+100) {

	if (Marke >  MA_WKEIT+50) AnzG++; 
	if (Marke <  MA_WKEIT+50) AnzV++; 
	if (Marke == MA_WKEIT+50) AnzR++; 

	Wert = (Marke - MA_WKEIT - 50) * 127.0 / 50.0;

      } else if (Marke >= MA_DIFF && Marke <= MA_DIFF+128) {

	if (Marke >  MA_DIFF+64) AnzG++; 
	if (Marke <  MA_DIFF+64) AnzV++; 
	if (Marke == MA_DIFF+64) AnzR++; 

	Wert = (Marke - MA_DIFF - 64) * 127.0 / 64.0;

      } else Error("unknown label");

      if (Wert == 0.0) continue;  // no draws

      Anz = SfAnz(&sf);

      ind = (Anz - I0) / IWIDTH;

      if (ind < 0)      ind = 0;
      if (ind > INUM-1) ind = INUM-1;
      
      num[ind]++;

      if (Wert < 0) num0[ind]++; else num1[ind]++;


      FOR (k, PATTNUM) PattVal[k] = 0;


#if FEATURENUM > 0

      { BRETT br;
	long  v;

	SfBrett(&sf, &br);

        FOR (i, FEATURENUM) {

          if (((v=features[i].func(&br)) <= features[i].means[ind]) ^ 
	      (Wert <= 0)) 
  	    features[i].err[ind]++;

	  // append values


	  if (Wert <= 0) { pVal = features[i].Val0; } 
          else 	         { pVal = features[i].Val1; }

	  if (pVal[ind].num < VAL_NUM) {

	    pVal[ind].values[pVal[ind].num++] = v;

	  }	 
	}
      }


#endif


      FOR (k, 2) {

	FOR (j, 4) {

	  FOR (l, PATTNUM) {

	    s = Pattern2Index(sf.p, &Patterns[l]);

	    //printf("::: %f\n", Patterns[l].tab[s].y[ind]);

#if 1
	    PattVal[l] += Patterns[l].tab[s].y[ind];
#else

	    // logit transformation

	    PattVal[l] += LOGIT(Patterns[l].tab[s].y[ind]/(2*127.0)+0.5);
	    printf("::: %f %f\n", Patterns[l].tab[s].y[ind], LOGIT(Patterns[l].tab[s].y[ind]/(2*127.0)+0.5));

#endif
	  } 

	  SfDrehen(&sf);
	}

	SfTransponieren(&sf);
      }


#if 0
      if (1 || Anz == OUT_NUM || Anz == OUT_NUM+1) {

	if (FRAN < SAVE_PERC) {
	  if (Wert <  0) printf(" 1 100 ");
	  if (Wert == 0) printf("50 100 ");
	  if (Wert >  0) printf("99 100 ");
	  
	  FOR (k, PATTNUM) printf("%.3f ", PattVal[k]);
	  printf("\n");
	}
      }
#endif

      FOR (k, PATTNUM) { 

	if ((PattVal[k] <= 0) ^ (Wert <= 0)) PattErr[k][ind]++;

	// append values

	if (Wert <= 0) { pVal = Patterns[k].Val0; } 
        else 	       { pVal = Patterns[k].Val1; }

	if (pVal[ind].num < VAL_NUM) {

	  pVal[ind].values[pVal[ind].num++] = round(10000*PattVal[k]);

/*
printf("%d %f\n", round(10000*PattVal[k]), PattVal[k]);
*/
	}
      }


 

#if 0
if (Anz == 42) {
  if (Wert < 0) printf("  1 100 ");
  else          printf(" 99 100 ");

  FOR (k ,PATTNUM) printf("%.1f ", PattVal[k]);

  printf("\n");
} 
#endif


    }
    fclose(fp);
  }


  FOR (k, PATTNUM) {

     printf("Pattern %d:\n", k);

     fShowPattern(stdout, &Patterns[k], 0);

     printf("\n");
  }
  

  printf("\nError:\n\n");

  FOR (k, PATTNUM) {

     printf("%2d: ", k);

     FOR (i, INUM)
       printf("%2d %2.1f ", 
	I0+i*IWIDTH, 
	(float)PattErr[k][i]*100.0 / (num[i]+0.0001));

     printf("\n");
  }


#if FEATURENUM > 0

  FOR (k, FEATURENUM) {

     printf("f%1d: ", k);

     FOR (i, INUM)
       printf("%2d %2.1f ", 
	 I0+i*IWIDTH, 
	 (float)features[k].err[i]*100.0 / (num[i]+0.0001));

     printf("\n");
  }

#endif



  printf("\nDiscord:\n\n");


  FOR (k, PATTNUM) {

     printf("%2d: ", k);

     FOR (i, INUM)
       printf("%2d %2.1f ",
	I0+i*IWIDTH, 
	100*discord(&Patterns[k].Val0[i], &Patterns[k].Val1[i]));

     printf("\n");
  }


#if FEATURENUM > 0

  FOR (k, FEATURENUM) {

     printf("f%1d: ", k);

     FOR (i, INUM)
       printf("%2d %2.1f ",
	I0+i*IWIDTH, 
	100*discord(&features[k].Val0[i], &features[k].Val1[i]));

     printf("\n");
  }

#endif




  return 0;
}



#if 0

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},


  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,0,0,1,0,0,0,
      0,0,0,0,1,1,0,0,0,0,
      0,0,0,0,1,1,0,0,0,0,
      0,0,0,1,0,0,1,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,1,1,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}



  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,1,1,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,1,1,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,1,1,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,1,1,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,1,0,0,
      0,0,0,0,0,0,1,0,0,0,
      0,0,0,0,0,1,0,0,0,0,
      0,0,0,0,1,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,0,0,0,0,0,1,0,0,
      0,0,0,0,0,0,1,0,0,0,
      0,0,0,0,0,1,0,0,0,0,
      0,0,0,0,1,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,0,0,0,0,1,0,0,0,
      0,0,0,0,0,1,0,0,0,0,
      0,0,0,0,1,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,0,0,0,1,0,0,0,0,
      0,0,0,0,1,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,0,0,1,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,0,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,1,1,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,1,1,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,1,1,0,
      0,0,0,0,0,0,0,1,1,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,1,1,0,
      0,1,1,0,0,0,0,1,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}, 


  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,0,0,1,1,1,0,
      0,0,1,0,0,0,0,1,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,0,0,1,1,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}



  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,0,0,0,0,0,0,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0
  }},


  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},


  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,0,1,1,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},


  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,1,0,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,0,0,0,0,1,1,0,
      0,1,1,1,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }}

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},



  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,1,1,1,0,
      0,0,1,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},


  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,1,1,1,0,
      0,0,1,0,0,0,0,1,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,1,1,1,1,0,0,0,0,
      0,1,1,1,1,1,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},


  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0, 
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,1,0,
      0,1,0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,1,1,1,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},


  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,1,1,1,1,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,0,1,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,1,1,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,0,1,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
  }}

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,0,0,
      0,0,1,1,1,1,0,0,0,0,
      0,0,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,1,1,1,0,0,0,0,0,
      0,0,1,1,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,0,0,0,0,0,
      0,0,1,1,1,0,0,0,0,0,
      0,0,1,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,1,1,0,0,0,0,0,
      0,0,0,1,1,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
  }},

  {{
      0,0,0,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,1,1,0,0,0,0,0,0,0,
      0,0,0,1,1,0,0,0,0,0,
      0,0,0,1,1,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
  }},






#endif