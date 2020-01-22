// ZigZagScan.cpp : Defines the entry point for the console application.
/***************************************************************************
    begin                : Dec 8 2005
    copyright            : (C) 2005 by Asad Ali
    email                : asad_82@yahoo.com
 ***************************************************************************/

// Programmed by Asad Ali
// sites.google.com/site/asad82

#include "stdafx.h"
#include "ZigZagScan.h"
#define N 8

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object
void ZigZagGetScan();
void ZigZagPutScan();


CWinApp theApp;

using namespace std;
double * zigzagOrder;
		double dataBlock2D[N][N]={ 
							{140 ,144, 147, 140, 140, 155, 179, 175},
							{144, 152, 140, 147, 140, 148, 167, 179},
							{152, 155, 136, 167, 163, 162, 152, 172},
							{168, 145, 156, 160, 152, 155, 136, 160},
							{162, 148, 156, 148, 140, 136, 147, 162},
							{147, 167, 140, 155, 155, 140, 136, 162},
							{136, 156, 123, 167, 162, 144, 140, 147},
							{148, 155, 136, 155, 152, 147, 147, 136}		
							};



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		//CString strHello;
		//strHello.LoadString(IDS_HELLO);
		//cout << (LPCTSTR)strHello << endl;
	ZigZagGetScan();
	for(int i=0;i<64;i++)
		printf("%1.0f , ",zigzagOrder[i]);

	for( i=0;i<8;i++)
		for(int j=0;j<8;j++)
			dataBlock2D[i][j]=0;

	ZigZagPutScan();

//	for( i=0;i<8;i++)
//		for(int j=0;j<8;j++)
//			printf("%4.0f , ",dataBlock2D[i][j]);



	}

	return nRetCode;
}




void ZigZagGetScan()
{

	int j=0,count=0,col=0,i,index=0,k=0;
	double * tempStore;
	tempStore = new double [8];
	zigzagOrder = new double[64];

//************* Get the First half of the data ***************//
	for(i=0;i<7;i++)
	{
		if(i==0)
			zigzagOrder[count++] = dataBlock2D[i][i]; 

		if(i > 0)
		{
			index=0;
			for(k=i,col=0;k>=0;k--,col++)
				tempStore[index++] = dataBlock2D[k][col];

			
			if(i%2==0)
			{
				for(k=0;k<index;k++)
					zigzagOrder[count++] = tempStore[k]; 
			}
			else
			{
				for(k=index-1;k >= 0;k--)
					zigzagOrder[count++] = tempStore[k]; 
			}

		}// end of if


	}// end of for loop

//************* Get the second half of the data ***************//
	for(i=0;i<8;i++)
	{

			index=0;
			for(k=i,col=7;k<8;k++,col--)
				tempStore[index++] = dataBlock2D[k][col];

			
			if(i%2==0)
			{
				for(k=0;k<index;k++)
					zigzagOrder[count++] = tempStore[k]; 
			}
			else
			{
				for(k=index-1;k >=0;k--)
					zigzagOrder[count++] = tempStore[k]; 
			}


	}// end of for loop




}// end of function


void ZigZagPutScan()
{
	int j=0,count=0,col=0,i,index=0,k=0,m=0;
	double * tempStore;
	tempStore = new double [8];
	//zigzagOrder = new double[64];

//************* Get the First half of the data ***************//
	for(i=0;i<7;i++)
	{
		if(i==0)
			 dataBlock2D[i][i] = zigzagOrder[count++]; 

		if(i > 0)
		{
			index=0;
			if(i%2==0)
			{
				for(k=0,m=i;m>=0;k++,m--)
				{
					tempStore[k] = zigzagOrder[count++];
					index++;
				}
			}
			else
			{
				for(k=0,m=i;m>=0;k++,m--)
				{
					tempStore[i-k] = zigzagOrder[count++];
					index++;
				}
			}

			for(k=i,col=0;k>=0;k--,col++)
				  dataBlock2D[k][col] = tempStore[col];


		}// end of if


	}// end of for loop

//************* Get the second half of the data ***************//
	for(i=0;i<8;i++)
	{		
			index=0;
			if(i%2==0)
			{
				for(m=i;m<8;m++)
				{
					 tempStore[index++] = zigzagOrder[count++];
				}
			}
			else
			{
				for(j=0;j<8;j++)
					tempStore[j]=0;

				for(m=i;m<8;m++)
				{
					tempStore[7-m] = zigzagOrder[count++];
					index++;
				}
			}

			index=0;
			for(k=i,col=7;k<8;k++,col--)
				  dataBlock2D[k][col] = tempStore[index++];


	}// end of for loop

	for( i=0;i<8;i++)
	{
		cout<<"\n";
		for(int j=0;j<8;j++)
			printf("%4.0f , ",dataBlock2D[i][j]);
	}

}// end of function
