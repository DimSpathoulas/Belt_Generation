// Spathoulas Dimitris

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#define N 21
#define M 21
#define NM 5
#define K 5
#define Td 10.0 // Nm
#define vel_sub 0.9
#define a_par_min 0.3 // m
#define a_par_max 0.7 // m
#define M_PI 3.141592
#define vel_max 40.0 // m/s
#define L_max 1.3 // m
#define n2_min 720.0 // rpm
#define n1_max 140.0 // rpm giati den ua antejei kai poly parapano
#define ang_vel_1_max 13.0 // rad/s 12.56
char m[64];
char name[64];
FILE *fptr=NULL;
int i,j,k,v;
double dd_1[N] = {0.08,0.09,0.1,0.112,0.125,0.14,0.16,0.18,0.2,0.224,0.25,0.28,0.315,0.355,0.4,0.45,0.5,0.56,0.63,0.71,0.8};
double dd_2[M] = {0.0315,0.0355,0.04,0.045,0.05,0.056,0.063,0.071,0.08,0.09,0.1,0.112,0.125,0.14,0.16,0.18,0.2,0.224,0.25,0.28,0.315};
double bbtr[NM] = {0.025,0.032,0.04,0.05,0.063};
double bb[NM] = {0.02 , 0.025 , 0.032, 0.04 , 0.05};
double trans;
int kk=0;
double L;
double s;
double f;
double velocity;
double a;
double ang_vel;


int main() {
	printf("Create a NEW file for data: ");
	scanf("%s",m);
	sprintf(name,"%s.txt",m);
	fptr=fopen(name,"w");
							
	if (fptr==NULL) {
		printf("\nfile couldnt be created! \n");	
	}
								
	else {
		for (i=0;i<N;i++) {
				for (j=0;j<M;j++) {
					trans = (dd_1[i]/dd_2[j]);
					if ( (n2_min/trans) < n1_max ) {
						a = fmin(((1.5)*(dd_1[i]+dd_2[j])),fmax( ((1.5*dd_2[j])+(dd_1[i]/2.0)),dd_1[i]));
						if ( (a_par_min<a) && (a_par_max>a) ) {
							L = (   (a*2.0) +  (M_PI*((dd_1[i]+dd_2[j])/2.0)) + ( (1.0/a)*pow((dd_1[i]-dd_2[j])/2.0,2.0) ) );
							if (L < L_max) {
								f = M_PI - (2.0*asin((dd_1[i]-dd_2[j])/(2.0*a)));
								ang_vel=((2.0*M_PI)*(n2_min/(trans*60.0)));
								velocity =ang_vel*(dd_1[i]/2.0);
								printf("  vel = %3.3lf ",velocity);
								if ((velocity<vel_max)&&(ang_vel<=ang_vel_1_max)) {
									fprintf(fptr,"%3.3lf m || %3.3lf m || a = %3.4lf m || trans = %3.3lf || L = %4.4lf m || f = %4.4lf rad || vel = %4.4lf || ang_vel = %4.4lf \n",dd_1[i],dd_2[j],a,trans,L,f,velocity,ang_vel);
									kk++; }
							}
						} 			
					}
					s=0.0;
					trans= 0.0;
					a = 0.0;
					f = 0.0;
					L =0.0;
					velocity = 0.0;
					ang_vel=0.0;
				}
		}
	}
	fclose(fptr);
	printf("\n\n%3d",kk);
	
return 0;
}
