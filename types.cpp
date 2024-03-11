#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#define n 8
#define M 30
#define NM 5
#define K 5
#define factor 1.0*pow(10.0,6.0)
#define omagad 13
#define M_E 2.7182819
#define yoaga 64
#define grav 9.81

// HYPERPAR
#define KG_MAX 0.4
#define vel_mx_f 4.5
#define Td  10.0 // Nm
#define H_min 15000.0
#define vel_sub 0.67
#define safety_f 0.85

double bbtr[NM] = {0.025,0.032,0.04,0.05,0.063};
double bb[NM] = {0.02 , 0.025 , 0.032, 0.04 , 0.05};
FILE *fptr;
FILE *fptr1;
int m;
char name[yoaga];
int i,j,x;
char name1[yoaga];
int counter = 0;
struct ttls {
	double obj[n];
	// dd_1[i], dd_2[j], a, trans, L, f, velocity, ang_vel
};
struct ttls alts[M];

struct typ {
	
	double Eb; // N/mm2
	double gamma; // kg/m3
	double Sall; // N/mm2
	double dsm;
	double bmax;
	double velmax;
	double s_min;
	double s_max;
	double trib;
	double scor;
};
struct typ type[14]; // 3 subtypes for 4 types 2 subs for 1 (+1 for assurance) 

double s=0.0;
double e =0.0;
double Sf=0.0;
double S_1=0.0;
double S_2= 0.0;
double S_0 = 0.0;
double ss_0=0.0;
double s_b1=0.0;
double s_k=0.0;
double s_u=0.0;
double seq=0.0;
double H = 0.0;
double B = 0.0;
int test = 0;
double KG = 0.0;
int main() {

	do {
	printf("Please enter number of alternatives: ");
	scanf("%d",&m); }
	while (!(m<M) );
	
	// FILE OPEN
	printf("\nWrite name of txt file containing values: ");
	scanf("%s",&name);

	fptr=fopen(name,"r");
		if (fptr==NULL) {
			printf("\nFile couldnt be found! \n");	
		}
	// TXT VALUES INPUT
		else {
		test = 1;
		for (i=0;i<m;i++){
				for (j=0;j<n;j++){
					fscanf(fptr,"%lf",&alts[i].obj[j]);
					printf("%4.3lf  ",alts[i].obj[j]); } printf("\n"); }
		}
	fclose(fptr);
	
	if (test==1) {
		test = 0;
	type[0].Eb=3.0;
	type[1].Eb=5.0;	
	type[2].Eb=7.0;
	type[0].dsm=20.0;
	type[1].dsm=25.0;
	type[2].dsm=35.0;
	
	type[3].Eb=4.0;
	type[4].Eb=6.0;	
	type[5].Eb=8.0;
	type[3].dsm=25.0;
	type[4].dsm=30.0;
	type[5].dsm=40.0;
	
	type[6].Eb=5.0;
	type[7].Eb=7.0;	
	type[8].Eb=9.0;
	type[6].dsm=30.0;
	type[7].dsm=35.0;
	type[8].dsm=45.0;
	
	type[9].bmax=7.5;
	type[10].bmax=7.5;	
	type[11].bmax=25.0;
	type[9].s_min=0.003;
	type[9].scor=1.3;
	type[9].s_max=0.007;
	type[10].s_min=0.003;
	type[10].scor=1.1;
	type[10].s_max=0.007;
	type[11].s_min=0.003;
	type[11].scor=0.7;
	type[11].s_max=0.007;
	
	type[12].bmax=7.5;
	type[13].bmax=25.0;
	type[12].s_min=0.003;
	type[12].scor=1.2;
	type[12].s_max=0.008;
	type[13].s_min=0.003;
	type[13].scor=0.6;
	type[13].s_max=0.008;
	
	for (i =0;i<9;i++) {
		type[i].scor=1.0;
	}
	
	
	
	for (i=0;i<3;i++) {
		type[i].Sall=0.44;
		type[i].bmax=25.0;
		type[i].gamma=900.0;
		type[i].velmax=50.0*vel_sub;
		type[i].trib=0.3 + ( (type[i].velmax/vel_mx_f)/100.0);  }
	
	for (i=3;i<6;i++) {
		type[i].Sall=0.44;
		type[i].bmax=10.0;
		type[i].gamma=950.0;
		type[i].velmax=40.0*vel_sub;
		type[i].trib=0.3 + ( (type[i].velmax/vel_mx_f)/100.0); }
	
	for (i=6;i<9;i++) {
		type[i].Sall=0.39;
		type[i].bmax=5.0;
		type[i].gamma=1000.0;
		type[i].velmax=30.0*vel_sub;
		type[i].trib=0.3 + ( (type[i].velmax/vel_mx_f)/100.0); }
	
	for (i=9;i<12;i++) {
		type[i].Sall=0.39;
		//type[i].bmax=5.0;
		type[i].gamma=1200.0;
		type[i].velmax=40.0*vel_sub;
		type[i].trib=0.5;
		type[i].dsm=30.0; }
		
		
	for (i=12;i<14;i++) {
		type[i].Sall=0.44;
		type[i].gamma=1250.0;
		type[i].velmax=40.0*vel_sub;
		type[i].trib=0.5;
		type[i].dsm=25.0; }
	
	for(i=0;i<8;i+=3) {
		type[i].s_min=0.003;
		type[i].s_max=0.007;
	}
	for(i=1;i<9;i+=3) {
		type[i].s_min=0.008;
		type[i].s_max=0.012;
	}
	for(i=2;i<10;i+=3) {
		type[i].s_min=0.014;
		type[i].s_max=0.020;
	}
	
	for (i=9;i<14;i++){
		type[i].Eb=5.0;
	}
	printf("\nWrite name of txt file you want to save final alternatives (the empty lines indicate new type): ");
			scanf("%s",&name1);
			fptr1=fopen(name1,"w");
			if (fptr1==NULL) {
			printf("\nFile couldnt be found! \n");	
				}
						// TXT VALUES INPUT
			else { 
	
	for ( x = 0 ; x < 14; x ++) {
		if (test == 3 ) { test=0;  }			// kai fprintf						
		test += 1;
		if (test==1 ) {
				fprintf(fptr1,"\n\n\n"); fprintf(fptr1,"%d\n\n\n",counter); counter = 0;
						}
		for ( i = 0; i < m ; i++) {
		
			if (type[x].velmax > alts[i].obj[6]) { 
				s = type[x].scor*(alts[i].obj[0]/(1.75*type[x].dsm) ); //printf("s = %4.4lf\n",s);
				if ((s > type[x].s_min)&&(s < type[x].s_max)) {
		
					Sf = (Td/(alts[i].obj[0]/2.0))/grav; //printf("SF IS %4.4lf",Sf); //kp
					e = pow(M_E,(alts[i].obj[5]*type[x].trib)); //printf("trib is %3.3lf    e is %4.4lf  \n",type[x].trib,e); 
					S_2 = Sf/(e-1); //printf("  S2 is %4.4lf",S_2);
					S_1 = Sf + S_2; //printf("   S1 is %4.4lf",S_1);
		     		S_0 = ((S_1+S_2)/2.0);	//printf("  S0 is %4.4lf\n",S_0);
		     		
					for (j = 0 ; j< NM ; j++ ) {
						ss_0= (S_0/(bb[j]*s*factor)); //printf("ss_0 = %3.3lf\n",ss_0); // kp/mm2
						s_k= ((S_1-S_2)/(2.0*bb[j]*s*factor)); //printf("s_k = %12.7lf\n",s_k); // kp/mm2
						s_u= ((type[x].gamma/1000.0)*(pow(alts[i].obj[6],2.0)))/(1000.0*9.81); //printf("s_u = %3.9lf\n",s_u); // kp/m2
						s_b1 = (type[x].Eb)*(s/alts[i].obj[0]); //printf("sb1 = %3.3lf\n",s_b1); // kp/mm2
						seq =( ss_0 + s_k + s_u + s_b1 ); // m2 - > mm2 10^6
					//	printf("seq is %5.4lf\n",seq);
					
						if (seq<(type[x].Sall*safety_f)) {
							B = (2.0*alts[i].obj[6])/alts[i].obj[4]; //printf("%4.4lf  \n",B);
							H = (((factor*10.0)/(3600.0*B))*(pow(((type[x].Sall*safety_f)/seq),6.0))); //printf("%4.4lf \n",H);
							KG = (bb[j]*alts[i].obj[4]*s*type[x].gamma);
							
							if ( ( H > H_min  ) && (KG < KG_MAX) ) {
								counter++;
								// d_1 d_2 b s L b*s*L*gamma Seq H
								fprintf(fptr1,"%4.4lf || %4.4lf || %4.4lf || %4.4lf || %4.4lf || %4.4lf || %4.4lf || %4.4lf \n",alts[i].obj[0],alts[i].obj[1],bb[j],s,alts[i].obj[4],KG,seq,H);
							} 
						}
					KG = 0.0;
					H = 0.0;
					B = 0.0;
					ss_0=0.0;
					s_k=0.0;
					s_u=0.0;
					s_b1=0.0;
					seq=0.0;
					}
						
				}
				
			}
			e=0.0;
			S_0=0.0;
			S_2=0.0;
			S_1=0.0;
			s=0.0;
		
		}

	}
	 
	fprintf(fptr1,"%d\n\n\n",counter);
	} fclose(fptr1);
}
	
	
	
return 0;
}
