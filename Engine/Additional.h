////////////////////////////////////////////////////////////
//
//������ ������������� ������� ������.
//
////////////////////////////////////////////////////////////

#include "Engine.h"

inline int randint( int low, int high )
{
//	if (high==low) return low;
	return (rand() % (high + 1 - low)) + low;
}

/*float Abs(float in)
{
 if (in<0) in = -in;
 return in;
}*/

BYTE GetAngle(int ip,int jp,int id,int jd)
{
	LookUp.LogMessage("ip=%d jp=%d id=%d jd=%d->\n",ip,jp,id,jd);
	if (ip==id){
		LookUp.LogMessage("if 0\n");
		if (jp>jd) return DIR_LEFT;
		else return DIR_RIGHT;
	}
	if(ip%2/*==1*/)OffSet2=14;//�����/���
	else OffSet2=0;
 	int xp=jp*26+OffSet2;
	int yp=ip*7;
	if(id%2/*==1*/)OffSet2=14;//�����/���
	else OffSet2=0;
 	int xd=jd*26+OffSet2;
	int yd=id*7;
	LookUp.LogMessage("yp=%d xp=%d yd=%d xd=%d\n",yp,xp,yd,xd);
	float tgx=fabs(xp-xd)/fabs(yp-yd);//tg x
	LookUp.LogMessage("TanX=%f\n",tgx);
	if (yp<yd&&xp<=xd){
		LookUp.LogMessage("if 1\n");
		if (tgx>=0&&tgx<=0.414) return DIR_DOWN;
		if (tgx>0.414&&tgx<=2.414) return DIR_RIGHTDOWN;
		if (tgx>2.414) return DIR_RIGHT;
	}
	else 
	if (yp>yd&&xp<=xd){
		LookUp.LogMessage("if 2\n");
		if (tgx>=0&&tgx<=0.414) return DIR_UP;
		if (tgx>0.414&&tgx<=2.414) return DIR_UPRIGHT;
		if (tgx>2.414) return DIR_RIGHT;
	}
	else
	if (yp<yd&&xp>=xd){
		LookUp.LogMessage("if 3\n");
		if (tgx>=0&&tgx<=0.414) return DIR_DOWN;
		if (tgx>0.414&&tgx<=2.414) return DIR_DOWNLEFT;
		if (tgx>2.414) return DIR_LEFT;
	}
	else
	if (yp>yd&&xp>=xd){
		LookUp.LogMessage("if 4\n");
		if (tgx>=0&&tgx<=0.414) return DIR_UP;
		if (tgx>0.414&&tgx<=2.414) return DIR_LEFTUP;
		if (tgx>2.414) return DIR_LEFT;
	}
	LookUp.LogMessage("if 5\n");
}

void SetR(RECT &rect,int x,int y,int xl,int yl){
	rect.left = x;
	rect.right = x+xl;
	rect.top = y;
	rect.bottom = y+yl;
} 

void insertItem(QUEUE **ppQueue, INDEX nItem)
{
  QUEUE *pNewItem;
  QUEUE *pCurItem = *ppQueue; // ������� - ������ �������
  QUEUE *pPreItem = 0;
  while(pCurItem)
  {
    // ������������ � ����� �������
    pPreItem = pCurItem;
    pCurItem = pCurItem->next;
  }
  // ����������� ������ ��� ��������� ��� �������� �������
  pNewItem = (QUEUE *)malloc(sizeof(QUEUE));
  
  // ��������� �������������� ����
  pNewItem->info = nItem;
  if(pPreItem)
  {
    // ���� ������� �����, ������ ����� ������� �� �������
    pNewItem->next = 0;
    pPreItem->next = pNewItem;
  }
  else
  {
    // � ��������� ������ �������� ��� � �����
    *ppQueue = pNewItem;
    (*ppQueue)->next = 0;
  }
}

INDEX removeItem(QUEUE **ppQueue, int *nError)
{
  QUEUE *pOldItem = *ppQueue;
  INDEX nOldInfo;
  if(*ppQueue)
  {
    // ���� ������� �� ������ - ��������� �������
    nOldInfo = pOldItem->info;
    *ppQueue = (*ppQueue)->next;
    // � ����������� ������
    free(pOldItem);
    *nError = 0;
  }
  else
    // � ��������� ������ ������
    *nError = 1;
  return nOldInfo;
}

BYTE tEngine::BlitChar(int x,int y,char chr,BYTE nFontSurf)
{
	BYTE zdvig;
	switch (chr)
	{
		case ' ':SetR(rect,0,0,0,0);
			zdvig = 6;
		break;
		case '�':SetR(rect,0,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,11,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,21,0,11,15);	
			zdvig = 11;
		break;
		case '�':SetR(rect,30,0,7,15);
			zdvig = 7;
		break;
		case '�':SetR(rect,36,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,47,0,11,15);
			zdvig = 11;
		break;
		case '�':SetR(rect,56,0,11,15);
			zdvig = 11;
		break;
		case '�':SetR(rect,67,0,14,15);
			zdvig = 14;
		break;
		case '�':SetR(rect,80,0,7,15);
			zdvig = 7;
		break;
		case '�':SetR(rect,86,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,96,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,106,0,10,15);
			zdvig = 10;
		break;
		case '�':SetR(rect,116,0,9,15);
			zdvig = 9;
		break;
		case '�':SetR(rect,125,0,13,15);
			zdvig = 13;
		break;
		case '�':SetR(rect,137,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,147,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,158,0,10,15);
			zdvig = 10;
    	break;
		case '�':SetR(rect,167,0,11,16);
			zdvig = 11;
		break;
		case '�':SetR(rect,177,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,188,0,8,15);
			zdvig = 8;
		break;
		case '�':SetR(rect,195,0,11,16);
			zdvig = 11;
		break;
		case '�':SetR(rect,205,0,16,16);
			zdvig = 16;
		break;
		case '�':SetR(rect,220,0,11,15);
			zdvig = 11;
		break;
		case '�':SetR(rect,230,0,12,15);
			zdvig = 12;
		break;
		case '�':SetR(rect,241,0,10,15);
			zdvig = 10;
		break;
		case '�':SetR(rect,251,0,14,15);
			zdvig = 14;
		break;
		case '�':SetR(rect,265,0,16,15);
			zdvig = 16;
    	break;
		case '�':SetR(rect,280,0,10,15);
			zdvig = 10;
		break;
		case '�':SetR(rect,289,0,14,15);
			zdvig = 14;
		break;
		case '�':SetR(rect,302,0,8,15);
			zdvig = 8;
		break;
		case '�':SetR(rect,309,0,10,15);
			zdvig = 10;
		break;
		case '�':SetR(rect,319,0,14,15);
			zdvig = 14;
		break;
		case '�':SetR(rect,332,0,9,15);
			zdvig = 9;
		break;
		case '1':SetR(rect,0,33,9,15);
			zdvig = 9;
		break;
		case '2':SetR(rect,9,33,10,15);
			zdvig = 10;
		break;
		case '3':SetR(rect,18,33,10,15);
			zdvig = 10;
		break;
		case '4':SetR(rect,27,33,10,15);
			zdvig = 10;
		break;
		case '5':SetR(rect,36,33,9,15);
			zdvig = 9;
    	break;
		case '6':SetR(rect,45,33,11,15);
			zdvig = 11;
		break;
		case '7':SetR(rect,55,33,10,15);
			zdvig = 10;
		break;
		case '8':SetR(rect,64,33,10,15);
			zdvig = 10;
		break;
		case '9':SetR(rect,74,33,9,15);
			zdvig = 9;
		break;
		case '0':SetR(rect,82,33,10,15);
			zdvig = 10;
		break;
		case '!':SetR(rect,91,33,6,15);
			zdvig = 6;
		break;
		case ':':SetR(rect,95,33,6,15);
			zdvig = 6;
		break;
		case '-':SetR(rect,99,33,8,15);
			zdvig = 8;
		break;
		case '=':SetR(rect,105,33,12,15);
			zdvig = 12;
		break;
		case '+':SetR(rect,115,33,12,15);
			zdvig = 12;
		break;
		case '(':SetR(rect,125,33,7,18);
			zdvig = 7;
		break;
		case ')':SetR(rect,132,33,7,18);
			zdvig = 7;
		break;
		case '*':SetR(rect,137,33,10,15);
			zdvig = 10;
		break;
	}
	BlitImage(x,y,nFontSurf,&rect);
	return zdvig;
}

int tEngine::BlitString(int x,int y,char chr[],BYTE nFontSurf)
{
	int c = 0;
	int zdvig = 0;
	while (chr[c])
	{
		zdvig+=BlitChar(x+zdvig,y,chr[c],nFontSurf);
		c++;
	}
	return zdvig;
}

void NewUnit(int ip,int jp,int who)
{
	if (Field[ip][jp]->pUnit) return;
	tUnit* pUnit;
	switch (who)
	{	
	case UNITTYPE_INFANTRY:
		pUnit = new tInfantry(ip,jp,CurRival);
		UnitList.push_front(pUnit);  
	break;
	case UNITTYPE_TURRET:
		pUnit = new tGunTurret(ip,jp,CurRival);
		UnitList.push_front(pUnit);
	break;
	case UNITTYPE_BARRAKS:
		pUnit = new tBarraks(ip,jp,CurRival);
		UnitList.push_front(pUnit);
	break;
	case UNITTYPE_UNIT:
	default:
	break;
	}
}


void tEngine::SetEngineThread(void (*thread)(void))
{
    // ���������� ������ �� ������
    m_thread = thread;
}

bool FindPath(INDEX Start,INDEX End,tINDEXList &InPathList)//����� ����
{
	time6=GetTickCount();
	INDEX cur, temp;
	int nError=0;
	int i,j;
	LookUp.LogMessage("*******************������ �������� ����*********\n");
	for (i=0;i<MapSizeI;i++)
	for (j=0;j<MapSizeJ;j++)
	{
		WA[i][j]->mark=0;//������� �� ���������� �������
		switch (Field[i][j]->Passability)
		{
		case FALSE:
			WA[i+2][j+2]->block=1;//1 �����������;
			                 //��� ��������� ��������� ������ 
			                 //�������������� ����������
		break;
		case TRUE:
			WA[i+2][j+2]->block=0;//1142856;//0 ���������
			if (Field[i][j]->pUnit!=NULL)//&&
				//Field[i+1][j+1]->pUnit->Whose!=)//�����...(���� ����� ������� ������������,����� - ���)
				WA[i+2][j+2]->block=1;//1142856;//������� ����
			//����� : ������� ����������� ��������� �����
		break;
		default:
			LookUp.LogMessage("��������� ������-��..:(!!!!!!!!!\n");
		break;
		}
	}
	time7=GetTickCount()-time6;
	/*for (i=0;i<MapSizeI+4;i++){
		for (j=0;j<MapSizeJ+4;j++)
			LookUp.LogMessage("%d",WA[i][j]->block);
		LookUp.LogMessage("\n");}*/
	////////////////////
	// ���������, � �������� �� ����� ����?
	if(WA[End.i+2][End.j+2]->block!=0)
		return false;
	// ������� � ������� ��������� �������
	//WA[Start.i+2][Start.j+2]->mark=1;
	temp.i = Start.i + 2;
	temp.j = Start.j + 2;
	insertItem(&Q,temp);
	// ����������� ����
	while (1)
	{
		// � �������� ������� ��������� � ������� �������
		cur=removeItem(&Q,&nError);
		// ���� ������� �����, �� �����
		if(nError==1) return false;
		// ���� �������� ������� - ����� ���� 
		if((cur.i==End.i+2)&&(cur.j==End.j+2.))
		{
			time8=GetTickCount()-time7-time6;
			LookUp.LogMessage("�������� ������� - ����� ����...\n");
			/*if (InPathList.empty()) 
				LookUp.LogMessage("empty..!\n");*/
			pINDEX = new INDEX;
			pINDEX->i=cur.i-2;
			pINDEX->j=cur.j-2;
			InPathList.push_front(pINDEX);
			while ((WA[cur.i][cur.j]->pI!=Start.i+2)||
				   (WA[cur.i][cur.j]->pJ!=Start.j+2)){
				//LookUp.LogMessage("������������ ����...(%d,%d)\n",cur.i,cur.j);
				pINDEX = new INDEX;
				pINDEX->i=WA[cur.i][cur.j]->pI-2;
				pINDEX->j=WA[cur.i][cur.j]->pJ-2;
				temp=cur;
				cur.i=WA[temp.i][temp.j]->pI;
				cur.j=WA[temp.i][temp.j]->pJ;
				//LookUp.LogMessage("...(pI=%d,pJ=%d)\n",WA[cur.i][cur.j]->pI,WA[cur.i][cur.j]->pJ);
				InPathList.push_front(pINDEX);
			}
			// ������� ������� �� ���������� ��� ���������
			do{
				cur=removeItem(&Q,&nError);
			}while(nError!=1);
			time9=GetTickCount()-time8-time7-time6;
			LookUp.LogMessage("time7=%d",time7);
			LookUp.LogMessage("time8=%d",time8);
			LookUp.LogMessage("time9=%d",time9);
			return true;
		}
		//LookUp.LogMessage("�������� �������� ���������\n");
		//LookUp.LogMessage("����� �������� (%d,%d):\n",cur.i,cur.j);
		// ���������� ������ �������� �����, ������������ 
		// ������� "cur" (�������� � �������� �������)
		//�����-�����/������(�����/���)
		//LookUp.LogMessage("�����-�����/������(��/�)...");
		if((WA[cur.i-1][cur.j]->mark==0) &&
		   (WA[cur.i-1][cur.j]->block==0))
		{
			// ����������� ...
			WA[cur.i-1][cur.j]->mark=1;
			WA[cur.i-1][cur.j]->pI=cur.i;
			WA[cur.i-1][cur.j]->pJ=cur.j;
			temp.i = cur.i-1;
			temp.j = cur.j;
			/*__asm{
				mov eax,cur
				sub eax.
				i,1
				mov temp.i eax//temp.i = cur.i-1;
				mov eax cur.j
				mov temp.j eax//temp.j = cur.j;
			};*/
			insertItem(&Q,temp);
//			LookUp.LogMessage("��\n");
		}
		//����-�����/������(�����/���)
		//LookUp.LogMessage("����-�����/������(��/�)...");
		if((WA[cur.i+1][cur.j]->mark==0) &&
		   (WA[cur.i+1][cur.j]->block==0))
		{
			// ����������� ...
			WA[cur.i+1][cur.j]->mark=1;
			WA[cur.i+1][cur.j]->pI=cur.i;
			WA[cur.i+1][cur.j]->pJ=cur.j;
			temp.i = cur.i+1;
			temp.j = cur.j;
			insertItem(&Q,temp);
//			LookUp.LogMessage("��\n");
		}
		if (cur.i%2==0)//������ i
		{
			//�����-�����
			//LookUp.LogMessage("�����-�����(����. �...)...");
			if((WA[cur.i-1][cur.j-1]->mark==0) &&
			   (WA[cur.i-1][cur.j-1]->block==0))
			{
				// ����������� ...
				WA[cur.i-1][cur.j-1]->mark=1;
				WA[cur.i-1][cur.j-1]->pI=cur.i;
				WA[cur.i-1][cur.j-1]->pJ=cur.j;
				temp.i = cur.i-1;
				temp.j = cur.j-1;
				insertItem(&Q,temp);
				//LookUp.LogMessage("��\n");
			}
			//����-�����
			//LookUp.LogMessage("����-�����(����. �...)...");
			if((WA[cur.i+1][cur.j-1]->mark==0) &&
			   (WA[cur.i+1][cur.j-1]->block==0))
			{
				// ����������� ...
				WA[cur.i+1][cur.j-1]->mark=1;
				WA[cur.i+1][cur.j-1]->pI=cur.i;
				WA[cur.i+1][cur.j-1]->pJ=cur.j;
				temp.i = cur.i+1;
				temp.j = cur.j-1;
				insertItem(&Q,temp);
//				LookUp.LogMessage("��\n");
			}
		}
		else //�������� i
		{
			//�����-������
//			LookUp.LogMessage("�����-������(����. ��...)...");
			if((WA[cur.i-1][cur.j+1]->mark==0) &&
			   (WA[cur.i-1][cur.j+1]->block==0))
			{
				// ����������� ...
				WA[cur.i-1][cur.j+1]->mark=1;
				WA[cur.i-1][cur.j+1]->pI=cur.i;
				WA[cur.i-1][cur.j+1]->pJ=cur.j;
				temp.i = cur.i-1;
				temp.j = cur.j+1;
				insertItem(&Q,temp);
//				LookUp.LogMessage("��\n");
			}
			//����-������
//			LookUp.LogMessage("����-������(����. ��...)...");
			if((WA[cur.i+1][cur.j+1]->mark==0) &&
			   (WA[cur.i+1][cur.j+1]->block==0))
			{
				// ����������� ...
				WA[cur.i+1][cur.j+1]->mark=1;
				WA[cur.i+1][cur.j+1]->pI=cur.i;
				WA[cur.i+1][cur.j+1]->pJ=cur.j;
				temp.i = cur.i+1;
				temp.j = cur.j+1;
				insertItem(&Q,temp);
//				LookUp.LogMessage("��-(t.i=%d t.j=%d)\n",temp.i,temp.j);
			}
		}
		// "�����"
//		LookUp.LogMessage("�����..m=%d b=%d...",WA[cur.i-2][cur.j]->mark,WA[cur.i-2][cur.j]->block);
		if((WA[cur.i-2][cur.j]->mark==0) &&	// ��� �� ����������� ?
		   (WA[cur.i-2][cur.j]->block==0))    // ��  ����������� ?
		{
			// ��������� ������
			WA[cur.i-2][cur.j]->mark=1;
			// �.�. ������ ��� �����������, �.�. ����� 
			// ������ ������� �� �� ������� (��������),
			// �� ��� ���������� ��������� � ��� �������
			// ������-��������
			WA[cur.i-2][cur.j]->pI=cur.i;
			WA[cur.i-2][cur.j]->pJ=cur.j;
			// ��������� ����� � ����� �������
			temp.i = cur.i-2;
			temp.j = cur.j;
			insertItem(&Q,temp);
//			LookUp.LogMessage("��\n");
		}
		// "����"
//		LookUp.LogMessage("����..m=%d b=%d...",WA[cur.i+2][cur.j]->mark,WA[cur.i+2][cur.j]->block);
		if((WA[cur.i+2][cur.j]->mark==0) &&
		   (WA[cur.i+2][cur.j]->block==0))
		{
			// ����������� ...
			WA[cur.i+2][cur.j]->mark=1;
			WA[cur.i+2][cur.j]->pI=cur.i;
			WA[cur.i+2][cur.j]->pJ=cur.j;
			temp.i = cur.i+2;
			temp.j = cur.j;
			insertItem(&Q,temp);
//			LookUp.LogMessage("��\n");
		}
		// "������"
//		LookUp.LogMessage("������..m=%d b=%d...",WA[cur.i][cur.j+1]->mark,WA[cur.i][cur.j+1]->block);
		if((WA[cur.i][cur.j+1]->mark==0) &&
		   (WA[cur.i][cur.j+1]->block==0))
		{
			// ����������� ...
			WA[cur.i][cur.j+1]->mark=1;
			WA[cur.i][cur.j+1]->pI=cur.i;
			WA[cur.i][cur.j+1]->pJ=cur.j;
			temp.i = cur.i;
			temp.j = cur.j+1;
			insertItem(&Q,temp);
//			LookUp.LogMessage("��\n");
		}
		// "�����"
//		LookUp.LogMessage("�����..m=%d b=%d...",WA[cur.i][cur.j-1]->mark,WA[cur.i][cur.j-1]->block);
		if((WA[cur.i][cur.j-1]->mark==0) &&
		   (WA[cur.i][cur.j-1]->block==0))
		{
			// ����������� ...
			WA[cur.i][cur.j-1]->mark=1;
			WA[cur.i][cur.j-1]->pI=cur.i;
			WA[cur.i][cur.j-1]->pJ=cur.j;
			temp.i = cur.i;
			temp.j = cur.j-1;
			insertItem(&Q,temp);
//			LookUp.LogMessage("��\n");
		}
		/*for (i=0;i<MapSizeI+4;i++){
			for (j=0;j<MapSizeJ+4;j++)
				LookUp.LogMessage("%d",WA[i][j]->mark);
			LookUp.LogMessage("\n");}*/
	}
}
