#include "engine\engine.h" 

LONG *WA[2004][1004];//������� ������ (Work Array)
LONG CurW;//������� �����(Current Wave)
int WC;//������� ����������� �����(Wave Counter)
LONG NTD;//Need To Delete
LONG g;
INDEX* temp;
INDEX* temp2;
int MapSizeI=8,MapSizeJ=4;
INDEX Min;
LONG min,c;

typedef INDEX* pLPINDEX;
typedef std::list<pLPINDEX  > tINDEXList; 
typedef std::list<pLPINDEX  >::iterator tINDEXListIterator; 

ENGINE_DLL tINDEXList BPIList; // (Buffer for Path INDEX List) ������
                               // ��� ����������� ������� ������ ���� 
tINDEXList PathList; //������ ��������� ����

//tINDEXListIterator INDEXLI2;

inline INDEX min8(INDEX pos)
{
	pos.i+=2; pos.j+=2;
	min=*WA[pos.i][pos.j-1];
	if (min>*WA[pos.i][pos.j+1])
		min=*WA[Min.i=pos.i][Min.j=pos.j+1];
	if (min>*WA[pos.i+2][pos.j])
		min=*WA[Min.i=pos.i+2][Min.j=pos.j];
	if (min>*WA[pos.i-2][pos.j])
		min=*WA[Min.i=pos.i-2][Min.j=pos.j];
	if (min>*WA[pos.i+1][pos.j])
		min=*WA[Min.i=pos.i+1][Min.j=pos.j];
	if (min>*WA[pos.i-1][pos.j])
		min=*WA[Min.i=pos.i-1][pos.j];
	if (temp2->i%2==0)//������ i
	{
		if (min>*WA[pos.i-1][pos.j-1])
			min=*WA[Min.i=pos.i-1][Min.j=pos.j-1];
		if (min>*WA[pos.i+1][pos.j-1])
			min=*WA[Min.i=pos.i+1][Min.j=pos.j-1];
	}
	else
	{
		if (min>*WA[pos.i-1][pos.j+1])
			min=*WA[Min.i=pos.i-1][Min.j=pos.j+1];
		if (min>*WA[pos.i+1][pos.j+1])
			min=*WA[Min.i=pos.i+1][Min.j=pos.j+1];
	}
	return Min;


}
void FindPathX(INDEX Start,INDEX End,tINDEXList &InPathList)//����� ����
{
	/*������� �������� ������ ���� �� ������ �����:
	    -��������� ���� �� ������
		-�����������, �� ��������� �� ����������� �� ���� �����
		 ->���� ���, �� ���� ��������� � ������ ���� �����,
		   ����� �� ��������� 
		 ->���� ��, �� ������������ ����� �� �������������� 
		   ���������� :(  (���������) ���������.
	*/

	/* ���������� �������� �������:
	   ����������� - ���� ����������� � "����" ����� � ���������,
		             ��������� ���������
	   �� ����������� - ���� �� ���������� :) ,� ����� ��������� �����
	   
		 � ������ ��������� ������ ������� - ���������� ������(���� � ������)
		 ����:
		 �������� �������� �����
	*/
	//������������� ������� � ����������� � �������� ������� �����
	for (i=0;i<MapSizeI+4;i++)
	for (j=0;j<MapSizeJ+4;j++)
		WA[i][j]=new LONG;
	//"���������" ��������� �������
	for (i=0;i<MapSizeI+4;i++)
	{
		*WA[i][0]=-1;
		*WA[i][1]=-1;
		*WA[i][MapSizeJ+1]=-1;
		*WA[i][MapSizeJ+2]=-1;
	}
	for (j=0;j<MapSizeI+2;j++)
	{
		*WA[0][j]=-1;
		*WA[1][j]=-1;
		*WA[MapSizeI+1][j]=-1;
		*WA[MapSizeI+2][j]=-1;
	}
	for (i=0;i<MapSizeI;i++)
	for (j=0;j<MapSizeJ;j++)
	{
		switch (Field[i][j]->Passability)
		{
		case FALSE:
			*WA[i+2][j+2]=-1;//-1 �����������;
			                 //��� ��������� ��������� ������ 
			                 //�������������� ����������
		break;
		case TRUE:
			*WA[i+2][j+2]=-2;//1142856;//-2 ���������
			if (Field[i][j]->pUnit!=NULL)//&&
				//Field[i+1][j+1]->pUnit->Whose!=)//�����...(���� ����� ������� ������������,����� - ���)
				*WA[i+2][j+2]=-1;//1142856;//������� ����
			//����� : ������� ����������� ��������� �����
		break;
		}
	}
	*WA[Start.i+2][Start.j+2]=-3;
	*WA[End.i+2][End.j+2]=0;
	*temp=End;
	BPIList.push_front(temp);
	NTD=g=1;
	CurW=0;
	while (1)
	{
		INDEXLI=BPIList.begin();
		while (INDEXLI!=BPIList.end())
		{
			WC=0;
			temp2=*INDEXLI;
			//��������������� ����� � ������ ������������:
			switch (*WA[temp2->i][temp2->j-1])//�����
			{
			case -2: *WA[temp2->i][temp2->j-1]=CurW+1;
				temp->i=temp2->i; temp->j=temp2->j-1;
				BPIList.push_back(temp);
				WC++;
				g++;
			break;
			case -3: goto CreatePath;
			break;
			}
			switch (*WA[temp2->i][temp2->j+1])//������
			{
			case -2: *WA[temp2->i][temp2->j+1]=CurW+1;
				temp->i=temp2->i; temp->j=temp2->j+1;
				BPIList.push_back(temp);
				WC++;
				g++;
			break;
			case -3: goto CreatePath;
			break;
			}
			switch (*WA[temp2->i+2][temp2->j])//�����
			{
			case -2: *WA[temp2->i+2][temp2->j]=CurW+1;
				temp->i=temp2->i+2; temp->j=temp2->j;
				BPIList.push_back(temp);
				WC++;
				g++;
			break;
			case -3: goto CreatePath;
			break;
			}
			switch (*WA[temp2->i-2][temp2->j])//����
			{
			case -2: *WA[temp2->i-2][temp2->j]=CurW+1;
				temp->i=temp2->i-2; temp->j=temp2->j;
				BPIList.push_back(temp);
				WC++;
				g++;
			break;
			case -3: goto CreatePath;
			break;
			}
			switch (*WA[temp2->i-1][temp2->j])//�����-�����/������(�����/���)
			{
			case -2: *WA[temp2->i-1][temp2->j]=CurW+1;
				temp->i=temp2->i-1; temp->j=temp2->j;
				BPIList.push_back(temp);
				WC++;
				g++;
			break;
			case -3: goto CreatePath;
			break;
			}
			switch (*WA[temp2->i+1][temp2->j])//����-������/�����(���/�����)
			{
			case -2: *WA[temp2->i+1][temp2->j]=CurW+1;
				temp->i=temp2->i+1; temp->j=temp2->j;
				BPIList.push_back(temp);
				WC++;
				g++;
			break;
			case -3: goto CreatePath;
			break;
			}
			if (temp2->i%2==0)//������ i
			{
				switch (*WA[temp2->i-1][temp2->j-1])//�����-�����
				{
		    	case -2: *WA[temp2->i-1][temp2->j-1]=CurW+1;
			    	temp->i=temp2->i-1; temp->j=temp2->j-1;
					BPIList.push_back(temp);
					WC++;
					g++;
				break;
				case -3: goto CreatePath;
				break;
				}
				switch (*WA[temp2->i+1][temp2->j-1])//����-�����
				{
		    	case -2: *WA[temp2->i+1][temp2->j-1]=CurW+1;
			    	temp->i=temp2->i+1; temp->j=temp2->j-1;
					BPIList.push_back(temp);
					WC++;
					g++;
				break;
				case -3: goto CreatePath;
				break;
				}
			}
			else //�������� i
			{
				switch (*WA[temp2->i-1][temp2->j+1])//�����-�����
				{
		    	case -2: *WA[temp2->i-1][temp2->j+1]=CurW+1;
			    	temp->i=temp2->i-1; temp->j=temp2->j+1;
					BPIList.push_back(temp);
					WC++;
					g++;
				break;
				case -3: goto CreatePath;
				break;
				}
				switch (*WA[temp2->i+1][temp2->j+1])//����-�����
				{
		    	case -2: *WA[temp2->i+1][temp2->j+1]=CurW+1;
			    	temp->i=temp2->i+1; temp->j=temp2->j+1;
					BPIList.push_back(temp);
					WC++;
					g++;
				break;
				case -3: goto CreatePath;
				break;
				};
			};
			NTD--;
			if (!BPIList.empty()) 
			{
				if (!NTD) 
				{
					
					for (INDEXLI2=BPIList.begin(),c=1;c<=g-WC;c++)
						INDEXLI2=BPIList.erase(INDEXLI2);
					NTD=g;
					g=0;
					break;
				}
			}
			else goto CreatePath;		//������ ����(���� �� ������)
		};//while
		CurW++;
	};//while
CreatePath:
	PathList.clear();
	*temp=min8(Start);
	if (!*WA[temp->i][temp->j])
	{
		temp = new INDEX;
		PathList.push_back(temp);  
	}
	else
	{
		BPIList.clear();
		return;
	}
	while (1)
	{
		*temp=min8(*temp);
		if (!*WA[temp->i][temp->j])
		{
			temp = new INDEX;
			PathList.push_back(temp);
		}
		else 
		{
			BPIList.clear();
			return;
		}
	}
	BPIList.clear();
	//return;
}
