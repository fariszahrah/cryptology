#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };





FILE *inputs;
FILE *trace;

int intVal[600];
float output[256][600];//at the end this is the number of 1 bits that need to be set after the sbox
int i=0;

//now the double array for the traces
//it is 600x55
float traces[600][55];
char *traceTemp[55];

int main(){
inputs = fopen("./inputs1.dat", "r");
for(i=0;i<600;i++)
{
		fscanf(inputs, "%d,", &intVal[i]);
}

//now the next few for loops will deal with importing the TX.dat file into its appropriate array
trace = fopen("./T1.dat","r");

for(i=0;i<600;i++){
		for(int j=0;j<55;j++){
				fscanf(trace, "%f,", &traces[i][j]);
		}
}

//just for debugging purposes
for(int x=0;x<11;x++)
{
		for(i=0;i<55;i++)
		{
			//	printf("%f,",traces[x][i]);
		}
//		printf("\n\n");
}
 

/*
 *these next two nested for loops are taking the sbox value of all possible combinations 
 *of both the 600 values from the inputsX.day file and the 256 possible key value bytes
 *
 */
for(int x = 0; x<256; x++){
		for(int j=0;j<600;j++){
				output[x][j] = sbox[(intVal[j] ^ x)];
		}
}


/*now its time to mask and shift to extract the number of 1 bits
 * in each of the valeus i have derived
 */


for(i=0;i<256;i++){
		for(int j=0;j<600;j++){
				int sum=0;
				for(int len=0;len<8;len++){
						if(((unsigned char)output[i][j] & 1) == 1){
								sum++;
						}
						output[i][j] = (unsigned char)output[i][j] >> 1;
				}
				output[i][j] = sum;
		}
}



/*
 * Now to find the correlation
 *
 * first I will declare 2 arrays just to determine the averages of each sample.
 * it is needed in the formula so this should be helpful going forward.
 * next I will declare the final double array which will be 256x55. 
 * In theory one of these entries will be 1 (god damnit it better be lol).
 */
float traceAvg[55];
float inputAvg[256];

float traceSTD[55];
float inputSTD[256];

float correlation[256][55];

//here I am filling out the inputAvg array
for(i=0;i<256;i++)
{
		float avg=0;
		for(int j=0;j<600;j++)
		{
				avg = avg + output[i][j];
		}
		inputAvg[i]=(avg/600);
//		printf("%f\n",inputAvg[i]);
}

//here I am filling out the traceAvg array
//printf("here is the trace avg array\n");
for(i=0;i<55;i++)
{
		float avg =0;
		for(int j=0;j<600;j++)
		{
				avg = avg + traces[j][i];
		}
		traceAvg[i] = (avg/600);
		//printf("%f, ",traceAvg[i]);
}


//here I am filling out the input stadard deviation array
for(i=0;i<256;i++)
{
		float diff =0;
		for(int j=0;j<600;j++)
		{
				diff = diff + ((output[i][j]-inputAvg[i])* (output[i][j]-inputAvg[i]));
		}
		diff= diff / 600;
		diff = sqrt(diff);
		inputSTD[i]=diff;
}

//here I am filling out the trace standard deviation array
for(i=0;i<55;i++)
{
		float diff =0;
		for(int j=0;j<600;j++)
		{
//				printf("%f, %f\n", traces[j][i],traceAvg[i]);
				diff = diff + ((traces[j][i]-traceAvg[i])*(traces[j][i]-traceAvg[i]));
		//		printf("trace: %f, traceavg: %f\n", traces[j][i],traceAvg[i]); 
		}
		diff = diff / 600;
	//	printf("%lf. ", diff);
		diff = sqrt(diff);
		traceSTD[i]=diff;
		//printf("Trace standard deviation: %f\n, ",traceSTD[i]);
}


//ok now to the correlation formula
for(i=0;i<256;i++)
{
		for(int j=0;j<55;j++)
		{
				float corr=0;
				for(int k=0;k<600;k++)
				{
						corr = corr + ( ((output[i][k]-inputAvg[i]) / inputSTD[i]) * ((traces[k][j]-traceAvg[j]) / traceSTD[j]) );
				}
				corr = corr / 599;
				//printf("%f, ",corr);
				//correlation[i][j]=corr;
		}
}	

for(i=0;i<256;i++)
{
		float coefficient=0;
		for(int j=0;j<55;j++)
		{
				float xSum=0;
				float ySum =0;
				float sum=0;
				for(int k=0;k<600;k++)
				{
						float temp = (output[i][k]-inputAvg[i]) * (traces[k][j]-traceAvg[j]);
						float xTemp = (output[i][k]-inputAvg[i]) * (output[i][k]-inputAvg[i]);
						float yTemp = (traces[k][j]-traceAvg[j]) * (traces[k][j]-traceAvg[j]);
						sum = sum + temp;
						xSum = xSum + xTemp;
						ySum = ySum + yTemp;
				}
				coefficient = sum / sqrt((xSum * ySum));
				correlation[i][j] = coefficient; 
		}
}


//ok holy fuck 
//printf("HERE IS THE CORRELATION TABLE");
float max=0;
int maxByte=0;
float min=0;
int minByte=0;
for(i=0;i<256;i++)
{
		for(int j=0;j<55; j++){
				if(correlation[i][j] > max)
				{
						max = correlation[i][j];
						maxByte=i;
				}
				if(correlation[i][j] < min)
				{
						min = correlation[i][j];
						minByte = i;
				}
//				printf("%f,",correlation[i][j]);
		}
}

		printf("Max correlation: %f with byte: %d\n Min correlation: %f with byte:%d\n", max,maxByte,min, minByte);







return (0);
}










