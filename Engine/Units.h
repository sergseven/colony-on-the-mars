////////////////////////////////////////////////////////////
//
//������ ��������� ���������� ������ ��������� ������.
//
////////////////////////////////////////////////////////////


#include "System.h"

BOOL tUnit::Collision(tUnit* pUnit)
{
	return 0;
}

void tInfantry::Process(tUnit* pUnit)
{
	// �� ������ ������
	if(bDie) return;
	// ������� ��� �������, � ������� ���������������
	BYTE Type = pUnit->GetType();
	// ���� ������ ������ � �����, ���������� ��������� �� �����
	if(Type == UNITTYPE_INFANTRY) return;
	// ���� ���� ������������
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// ������� ������ ������ ���� ������
			//case UNITTYPE_INFANTRY:
			//	pUnit->Kill(); // ������� ������
			//break;
			default:
			break;
		} // switch
	} // if
} // Process()


BOOL tInfantry::Move()
{
	//LookUp.LogMessage("���� ������������ ���������� ������\n");
	// ����������?
	if(health>=H_DEAD||bDie) 
	{
		Kill();
		return FALSE;
	}
	// �������� ������� ��������
	/*if(Counter<1) Counter++;
	else{*/
		//LookUp.LogMessage("���� ����� ������������ ���������� ������....");
		//Counter = 0;
	LookUp.LogMessage("��......pAttUnit->Pos.i=%d pAttUnit->Pos.j=%d  pAttUnit=%d this=%d\n",pAttUnit->Pos.i,pAttUnit->Pos.j,pAttUnit,this);
	    if(pAttUnit&&pAttUnit->health>=H_DEAD){//����� ���-�� ������ ������ 
			pAttUnit=NULL;
			MessageMeAboutAllUnits(Pos);//������������� ������ � ������� ������...
		}
		if (pAttUnit&&(OSx==0&&OSy==0))
		{
			LookUp.LogMessage("���� �������\n");
			if(Pos.i%2/*==1*/)OffSet=14;//�����/���
			else OffSet=0;
			if(pAttUnit->Pos.i%2/*==1*/)OffSet2=14;//�����/���
			else OffSet2=0;
			vx=(Pos.j*26+14+OffSet)-(pAttUnit->Pos.j*26-2+OffSet2);
			vy=(Pos.i*7+12)-(pAttUnit->Pos.i*7-4);
			//len=sqrt(vx*vx+vy*vy);
			if (sqrt(vx*vx+vy*vy)<=GetRad())
			{
				Fire();//�����!!!!
				if (pAttUnit&&pAttUnit->Whose!=CurRival&&pAttUnit->pAttUnit==NULL)//����?
					pAttUnit->pAttUnit=this;//������ ������� ������������ ���������,������:) 
			}
			else{
				LookUp.LogMessage("��������� � ����������\n");
				PathList.clear();
				pINDEX = new INDEX;
				LookUp.LogMessage("pAttUnit->Pos.i=%d pAttUnit->Pos.j=%d  pAttUnit=%d\n",pAttUnit->Pos.i,pAttUnit->Pos.j,pAttUnit);
				switch (GetAngle(Pos.i,Pos.j,pAttUnit->Pos.i,pAttUnit->Pos.j))
				{
				case DIR_UP:pINDEX->i=Pos.i-2;
							pINDEX->j=Pos.j;
	    		break;
	    		case DIR_UPRIGHT:pINDEX->i=Pos.i-1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j+1;//�����
					else pINDEX->j=Pos.j;//���
	    		break;
		   	    case DIR_RIGHT:pINDEX->i=Pos.i;
							   pINDEX->j=Pos.j+1;
		    	break;
    			case DIR_RIGHTDOWN:pINDEX->i=Pos.i+1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j+1;//�����
					else pINDEX->j=Pos.j;//���

	    		break;
    			case DIR_DOWN:pINDEX->i=Pos.i+2;
							  pINDEX->j=Pos.j;
		    	break;
	    		case DIR_DOWNLEFT:pINDEX->i=Pos.i+1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j;//�����
					else pINDEX->j=Pos.j-1;//���

    			break;
	    		case DIR_LEFT:pINDEX->i=Pos.i;
							  pINDEX->j=Pos.j-1;
		    	break;
    			case DIR_LEFTUP:pINDEX->i=Pos.i-1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j;//�����
					else pINDEX->j=Pos.j-1;//���
	    		break;
				}
				PathList.push_front(pINDEX);
				Action=*pINDEX;
			}
		}
		if ((OSx==0&&OSy==0)&&(Pos.i!=Action.i||Pos.j!=Action.j)){
			//LookUp.LogMessage("Pos.i!=Action.i...\n");
			if (PathList.empty()){/*if(!Field[Action.i][Action.j]->pUnit){*/
Find:		 	LookUp.LogMessage("���� (%d,%d) ���� ���� � (%d,%d)\n",Pos.i,Pos.j,Action.i,Action.j);
				if (!FindPath(Pos,Action,PathList)){
					Action.i=Pos.i;//���� �� ������ - "�����������" ���� 
					Action.j=Pos.j;
					return TRUE;
				}				 
			}
			LookUp.LogMessage("������ ���� (%d,%d) ����� ���� � (%d,%d)\n",Pos.i,Pos.j,Action.i,Action.j);
			INDEXLI=PathList.begin();
			pINDEX=*INDEXLI;
			//LookUp.LogMessage("F->Pass=%d...F[%d][%d]->pUn=%d...this=%d\n",Field[pINDEX->i][pINDEX->j]->Passability,pINDEX->i,pINDEX->j,Field[pINDEX->i][pINDEX->j]->pUnit,this);
			if (Field[pINDEX->i][pINDEX->j]->Passability==TRUE&&
				Field[pINDEX->i][pINDEX->j]->pUnit==NULL){
				INDEX t=*pINDEX;//temp
				//LookUp.LogMessage("F->Pass=%d...F->pUn=%d\n",Field[pINDEX->i][pINDEX->j]->Passability,Field[pINDEX->i][pINDEX->j]->pUnit);
				Field[Pos.i][Pos.j]->pUnit=NULL;
				Angle=GetAngle(Pos.i,Pos.j,t.i,t.j);
				LookUp.LogMessage("AAAngle=%d\n",Angle);
				OSx=0;
				OSy=0;
				switch (Angle){
				case DIR_UP:OSy=14;
	     	   	break;
	        	case DIR_UPRIGHT:OSx=-14;
					    	     OSy=7;
	        	break;
		        case DIR_RIGHT:OSx=-28;
					LookUp.LogMessage("DIR_RIGHT case\n");
	           	break;
    	    	case DIR_RIGHTDOWN:OSx=-14;
					          	   OSy=-7;
	        	break;
        		case DIR_DOWN:OSy=-14;
		       	break;
    	    	case DIR_DOWNLEFT:OSx=14;
					              OSy=-7;
        		break;
	        	case DIR_LEFT:OSx=28;
	    	   	break;
    		   	case DIR_LEFTUP:OSx=14;
					            OSy=7;
	        	break;
				}
				Pos=*pINDEX;
				Field[Pos.i][Pos.j]->pUnit=this;
				MessageAllUnitsAboutMe(Pos);
				delete pINDEX;
				PathList.erase(INDEXLI);
			}
			else{
				PassCounter--;
				LookUp.LogMessage("NTD=%d\n",PassCounter);
				if (PassCounter==0){
					PassCounter=20;
					LookUp.LogMessage("goto <Find>\n" );
					goto Find;
				}//if (PassCounter==0){
			}//else{
		}//if (!OSx&&!OSy&&Pos.i!=Action.i||Pos.j!=Action.j){
		if (Frame==1){
			//LookUp.LogMessage("����������..Pos.i=%d Pos.j=%d Action.i=%d Action.j=%d\n",Pos.i,Pos.j,Action.i,Action.j);
			Frame=0;
		}//if (Frame==1){
		else{
			if (OSx||OSy/*||Pos.i!=Action.i||Pos.j!=Action.j*/){
				switch (Angle){
    			case DIR_UP:OSy--;
	    		break;
	    		case DIR_UPRIGHT:OSx+=2;
	   	    	OSy--;
	    		break;
		   	    case DIR_RIGHT:OSx+=2;
					LookUp.LogMessage("DIR_RIGHT case:OSx=%d\n",OSx);
		    	break;
    			case DIR_RIGHTDOWN:OSx+=2;
     			OSy++;
	    		break;
    			case DIR_DOWN:OSy++;
		    	break;
	    		case DIR_DOWNLEFT:OSx-=2;
		    	OSy++;
    			break;
	    		case DIR_LEFT:OSx-=2;
		    	break;
    			case DIR_LEFTUP:OSx-=2;
		    	OSy--;
	    		break;
				}
				// �������� ������� ����
			    Frame++; 
			}
		}
//	}
	return TRUE; // �� ����������
} // Move() 

void tInfantry::Fire()
{
	LookUp.LogMessage("���� �������\n");
	pAttUnit->health+=BYTE((randint(MinDimage,MaxDimage))/ 
	            (randint(pAttUnit->MinDefend,pAttUnit->MaxDefend)));
	if(pAttUnit->health>=H_DEAD){
		pAttUnit=NULL;
		MessageMeAboutAllUnits(Pos);
		LookUp.LogMessage("���� ����...\n");
	}
}

BOOL tGunTurret::Move()
{
	// ����������?
	if(health>=H_DEAD||bDie) 
	{
		Kill();
		return FALSE;
	}
    if(pAttUnit&&pAttUnit->health>=H_DEAD){//����� ���-�� ������ ������... 
		pAttUnit=NULL;
		MessageMeAboutAllUnits(Pos);//������������� ������ � ������� ������...
	}
	// �������� ������� ��������
	if(Counter<30) Counter++;
	else
	{
		Counter = 0;
		if (pAttUnit)
		{
			LookUp.LogMessage("���� �������\n");
			if(Pos.i%2/*==1*/)OffSet=14;//�����/���
			else OffSet=0;
			if(pAttUnit->Pos.i%2/*==1*/)OffSet2=14;//�����/���
			else OffSet2=0;
			vx=(Pos.j*26+14+OffSet)-(pAttUnit->Pos.j*26+14+OffSet2);
			vy=(Pos.i*7-4)-(pAttUnit->Pos.i*7+12);
			//len=sqrt(vx*vx+vy*vy);
			if (sqrt(vx*vx+vy*vy)<=GetRad()){
				Fire();//�����!!!!
				if (pAttUnit&&pAttUnit->Whose!=CurRival&&pAttUnit->pAttUnit==NULL)//����?
					pAttUnit->pAttUnit=this;//������ ������� ������������ ���������,������:) 
			}
		}
		// �������� ������� ����
		//Frame++; 
	}
	return TRUE; // �� ����������
} // Move() 

void tGunTurret::Fire()
{
	LookUp.LogMessage("���� ��������\n");
	pUnit2=new tRocket(Pos,pAttUnit->Pos,MinDimage,MaxDimage);
	UnitList.push_front(pUnit2);
	/*
	pAttUnit->health+=BYTE((randint(MinDimage,MaxDimage))/ 
	            (randint(pAttUnit->MinDefend,pAttUnit->MaxDefend)));*/
	if(pAttUnit->health>=H_DEAD){
		pAttUnit=NULL;
		MessageMeAboutAllUnits(Pos);
		LookUp.LogMessage("���� ����...\n");
	}
}

void tGunTurret::Process(tUnit* pUnit)
{
	/*// �� ������ ������
	if(bDie) return;
	// ���� ������ ������ � �����, ���������� ��������� �� �����
	if(pUnit->GetType()==UNITTYPE_INFANTRY) return;
	// ���� ���� ������������
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// ������� ������ ������ ���� ������
			//case UNITTYPE_INFANTRY:
			//	pUnit->Kill(); // ������� ������
			//break;
			default:
			break;
		} // switch
	} // if*/
} // Process()

BOOL tBarraks::Move()
{
	// ����������?
	if(health>=H_DEAD||bDie) 
	{
		Kill();
		return FALSE;
	}
	if (ThreadInd&&ThreadInd==UNITTYPE_INFANTRY)
	{
		Complite++;
		if (Complite>=100){
			ThreadInd=0;
			Complite=0;
    		if (Field[Pos.i+2][Pos.j]->pUnit==0)
				NewUnit(Pos.i+2,Pos.j,UNITTYPE_INFANTRY);
			else{
				int cc=0;
				do{
					if (Field[Pos.i+2+cc][Pos.j+1]->pUnit==0){
						NewUnit(Pos.i+2+cc,Pos.j+1,UNITTYPE_INFANTRY);
						break;
					}
					if (Field[Pos.i+2+cc][Pos.j-1]->pUnit==0){
						NewUnit(Pos.i+2+cc,Pos.j-1,UNITTYPE_INFANTRY);
						break;
					}
					if (Field[Pos.i+2+cc][Pos.j]->pUnit==0){
						NewUnit(Pos.i+2+cc,Pos.j,UNITTYPE_INFANTRY);
						break;
					}
					cc++;
				}while(1);
			}
		}
	}
	// �������� ������� ��������
	if(Counter<30) Counter++;
	else
	{
		Counter = 0;
		// �������� ������� ����
		//Frame++; 
	}
	return TRUE; // �� ����������
} // Move() 

void tBarraks::Process(tUnit* pUnit)
{
	/*// �� ������ ������
	if(bDie) return;
	// ���� ������ ������ � �����, ���������� ��������� �� �����
	if(pUnit->GetType()==UNITTYPE_INFANTRY) return;
	// ���� ���� ������������
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// ������� ������ ������ ���� ������
			//case UNITTYPE_INFANTRY:
			//	pUnit->Kill(); // ������� ������
			//break;
			default:
			break;
		} // switch
	} // if*/
} // Process()

BOOL tExplosion::Move()
{
	// ����������?
	if(bDie) return FALSE;
	// �������� ������� ��������
	if(Counter < 2) Counter++; 
	else{
		Counter = 0;
		if(Frame < 8) // �������� ������� ����
			Frame++;
		else
			return FALSE; // ����������
	}
	return TRUE; // �� ����������
} // Move() 

void tExplosion::Process(tUnit* pUnit)
{
	// �� ������ ������
	if(bDie) return;
	// ���� ������ ������ � �����, ���������� ��������� �� �����
	if(pUnit->GetType()==UNITTYPE_MEXPLOSION) return;
	// ���� ���� ������������
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// ������� ������ ������ ���� ������
			case UNITTYPE_INFANTRY:
				pUnit->Kill(); // ������� ������
			break;
			default:
			break;
		} // switch
	} // if
} // Process()

BOOL tRocket::Move()
{
	// ����������?
	if(bDie) return FALSE;
	// �������� ������� ��������
	/*if(Frame < 3){*/
		pr+=55;
		if (pr>=max_pr){
			pUnit2=new tExplosion(Target.y/7,Target.x/26,MinDimage,MaxDimage);
			UnitList.push_front(pUnit2);
			return FALSE;
		}
		// �������� ������� ����
		Frame++;
	/*}
	else Frame=0;*/
	return TRUE; // �� ����������
} // Move() 

void tRocket::Process(tUnit* pUnit)
{
	// �� ������ ������
	if(bDie) return;
	// ���� ������ ������ � �����, ���������� ��������� �� �����
	if(pUnit->GetType()==UNITTYPE_MEXPLOSION) return;
	// ���� ���� ������������
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// ������� ������ ������ ���� ������
			case UNITTYPE_INFANTRY:
				pUnit->Kill(); // ������� ������
			break;
			default:
			break;
		} // switch
	} // if
} // Process()

//���� - ��� �������, ���������� �� 2 ������� �.�.
void MessageAllUnitsAboutMe(INDEX pos){
	const MaxSight=1500;
	for(tUnitListIterator UnitLI=UnitList.begin();UnitLI!=UnitList.end();UnitLI++)
	{
		pUnit2=*UnitLI;
		//���� ����� ���� � ����� ����� ��� � "��������",�� ������������� �� ���� 
		if (pUnit2==Field[pos.i][pos.j]->pUnit||pUnit2->Whose==CurRival||pUnit2->health>=H_DEAD
			) continue;
		if(pos.i%2/*==1*/)OffSet2=14;//�����/���
		else OffSet2=0;
		int xp=pos.j*26+OffSet2;
		int yp=pos.i*7;
		if(pUnit2->Pos.i%2/*==1*/)OffSet2=14;//�����/���
		else OffSet2=0;
		int xd=pUnit2->Pos.j*26+OffSet2;
		int yd=pUnit2->Pos.i*7;
		if (abs(xp-xd)<=MaxSight&&abs(yp-yd)<=MaxSight)
			if (pUnit2->pAttUnit==NULL&&
				pUnit2->PathList.empty())
				pUnit2->pAttUnit=Field[pos.i][pos.j]->pUnit;
	}
}

void MessageMeAboutAllUnits(INDEX pos){
	const MaxSight=1500;
	if (Field[pos.i][pos.j]->pUnit->pAttUnit) return;
	for(tUnitListIterator UnitLI=UnitList.begin();UnitLI!=UnitList.end();UnitLI++){
		pUnit2=*UnitLI;
		//���� ����� ���� � ����� ����� ��� � "��������" ��� � ������,�� ������������ �� ���� 
		if (pUnit2==Field[pos.i][pos.j]->pUnit||pUnit2->Whose==CurRival||pUnit2->health>=H_DEAD) continue;
		if(pos.i%2/*==1*/)OffSet2=14;//�����/���
		else OffSet2=0;
		int xp=pos.j*26+OffSet2;
		int yp=pos.i*7;
		if(pUnit2->Pos.i%2/*==1*/)OffSet2=14;//�����/���
		else OffSet2=0;
		int xd=pUnit2->Pos.j*26+OffSet2;
		int yd=pUnit2->Pos.i*7;
		int absxo=0;
		int absyo=0;
		if (Field[pos.i][pos.j]->pUnit->pAttUnit){
			if(Field[pos.i][pos.j]->pUnit->pAttUnit->Pos.i%2/*==1*/)OffSet2=14;//�����/���
    		else OffSet2=0;
	    	int xa=Field[pos.i][pos.j]->pUnit->pAttUnit->Pos.j*26+OffSet2;
    		int ya=Field[pos.i][pos.j]->pUnit->pAttUnit->Pos.i*7;
			absxo=abs(xp-xa);//absx[old]-���������� �� ������� �����
		    absyo=abs(yp-ya);//absy[old]
		}
		int absxn=abs(xp-xd);//absx[new]-���������� �� �������� �������� ����� 
		int absyn=abs(yp-yd);//absy[new]
		if (absxn<=MaxSight&&absyn<=MaxSight)
			if (Field[pos.i][pos.j]->pUnit->PathList.empty()&&
				(!Field[pos.i][pos.j]->pUnit->pAttUnit||
				Field[pos.i][pos.j]->pUnit->pAttUnit&&(absxn<absxo&&absyn<absyo)))
				Field[pos.i][pos.j]->pUnit->pAttUnit=pUnit2;
	}
}