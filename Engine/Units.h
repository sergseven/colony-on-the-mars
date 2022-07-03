////////////////////////////////////////////////////////////
//
//Модуль обработки внутренних данных различных юнитов.
//
////////////////////////////////////////////////////////////


#include "System.h"

BOOL tUnit::Collision(tUnit* pUnit)
{
	return 0;
}

void tInfantry::Process(tUnit* pUnit)
{
	// на всякий случай…
	if(bDie) return;
	// Получим тип объекта, с которым взаимодействуем…
	BYTE Type = pUnit->GetType();
	// Если другой объект – взрыв, дальнейшая обработка не нужна
	if(Type == UNITTYPE_INFANTRY) return;
	// Если есть столкновение…
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// Взрывом задело объект типа “игрок”
			//case UNITTYPE_INFANTRY:
			//	pUnit->Kill(); // Убиваем игрока
			//break;
			default:
			break;
		} // switch
	} // if
} // Process()


BOOL tInfantry::Move()
{
	//LookUp.LogMessage("Юнит обробатывает внутренние данные\n");
	// Уничтожить?
	if(health>=H_DEAD||bDie) 
	{
		Kill();
		return FALSE;
	}
	// Изменяем счетчик анимации
	/*if(Counter<1) Counter++;
	else{*/
		//LookUp.LogMessage("Юнит начал обробатывать внутренние данные....");
		//Counter = 0;
	LookUp.LogMessage("до......pAttUnit->Pos.i=%d pAttUnit->Pos.j=%d  pAttUnit=%d this=%d\n",pAttUnit->Pos.i,pAttUnit->Pos.j,pAttUnit,this);
	    if(pAttUnit&&pAttUnit->health>=H_DEAD){//врага кто-то другой пришил 
			pAttUnit=NULL;
			MessageMeAboutAllUnits(Pos);//осматриваемся вокруг в поисках нового...
		}
		if (pAttUnit&&(OSx==0&&OSy==0))
		{
			LookUp.LogMessage("Юнит атакует\n");
			if(Pos.i%2/*==1*/)OffSet=14;//нечет/чет
			else OffSet=0;
			if(pAttUnit->Pos.i%2/*==1*/)OffSet2=14;//нечет/чет
			else OffSet2=0;
			vx=(Pos.j*26+14+OffSet)-(pAttUnit->Pos.j*26-2+OffSet2);
			vy=(Pos.i*7+12)-(pAttUnit->Pos.i*7-4);
			//len=sqrt(vx*vx+vy*vy);
			if (sqrt(vx*vx+vy*vy)<=GetRad())
			{
				Fire();//Огонь!!!!
				if (pAttUnit&&pAttUnit->Whose!=CurRival&&pAttUnit->pAttUnit==NULL)//враг?
					pAttUnit->pAttUnit=this;//первый уровень искусвенного интилекта,однако:) 
			}
			else{
				LookUp.LogMessage("двигаемся к противнику\n");
				PathList.clear();
				pINDEX = new INDEX;
				LookUp.LogMessage("pAttUnit->Pos.i=%d pAttUnit->Pos.j=%d  pAttUnit=%d\n",pAttUnit->Pos.i,pAttUnit->Pos.j,pAttUnit);
				switch (GetAngle(Pos.i,Pos.j,pAttUnit->Pos.i,pAttUnit->Pos.j))
				{
				case DIR_UP:pINDEX->i=Pos.i-2;
							pINDEX->j=Pos.j;
	    		break;
	    		case DIR_UPRIGHT:pINDEX->i=Pos.i-1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j+1;//нечет
					else pINDEX->j=Pos.j;//чет
	    		break;
		   	    case DIR_RIGHT:pINDEX->i=Pos.i;
							   pINDEX->j=Pos.j+1;
		    	break;
    			case DIR_RIGHTDOWN:pINDEX->i=Pos.i+1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j+1;//нечет
					else pINDEX->j=Pos.j;//чет

	    		break;
    			case DIR_DOWN:pINDEX->i=Pos.i+2;
							  pINDEX->j=Pos.j;
		    	break;
	    		case DIR_DOWNLEFT:pINDEX->i=Pos.i+1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j;//нечет
					else pINDEX->j=Pos.j-1;//чет

    			break;
	    		case DIR_LEFT:pINDEX->i=Pos.i;
							  pINDEX->j=Pos.j-1;
		    	break;
    			case DIR_LEFTUP:pINDEX->i=Pos.i-1;
					if (Pos.i%2/*==1*/) pINDEX->j=Pos.j;//нечет
					else pINDEX->j=Pos.j-1;//чет
	    		break;
				}
				PathList.push_front(pINDEX);
				Action=*pINDEX;
			}
		}
		if ((OSx==0&&OSy==0)&&(Pos.i!=Action.i||Pos.j!=Action.j)){
			//LookUp.LogMessage("Pos.i!=Action.i...\n");
			if (PathList.empty()){/*if(!Field[Action.i][Action.j]->pUnit){*/
Find:		 	LookUp.LogMessage("Юнит (%d,%d) ищет путь в (%d,%d)\n",Pos.i,Pos.j,Action.i,Action.j);
				if (!FindPath(Pos,Action,PathList)){
					Action.i=Pos.i;//путь не найден - "успокаиваем" юнит 
					Action.j=Pos.j;
					return TRUE;
				}				 
			}
			LookUp.LogMessage("Кажись юнит (%d,%d) нашел путь в (%d,%d)\n",Pos.i,Pos.j,Action.i,Action.j);
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
			//LookUp.LogMessage("продолжает..Pos.i=%d Pos.j=%d Action.i=%d Action.j=%d\n",Pos.i,Pos.j,Action.i,Action.j);
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
				// Изменяем текущий кадр
			    Frame++; 
			}
		}
//	}
	return TRUE; // Не уничтожать
} // Move() 

void tInfantry::Fire()
{
	LookUp.LogMessage("Юнит убивает\n");
	pAttUnit->health+=BYTE((randint(MinDimage,MaxDimage))/ 
	            (randint(pAttUnit->MinDefend,pAttUnit->MaxDefend)));
	if(pAttUnit->health>=H_DEAD){
		pAttUnit=NULL;
		MessageMeAboutAllUnits(Pos);
		LookUp.LogMessage("Юнит убил...\n");
	}
}

BOOL tGunTurret::Move()
{
	// Уничтожить?
	if(health>=H_DEAD||bDie) 
	{
		Kill();
		return FALSE;
	}
    if(pAttUnit&&pAttUnit->health>=H_DEAD){//врага кто-то другой пришил... 
		pAttUnit=NULL;
		MessageMeAboutAllUnits(Pos);//осматриваемся вокруг в поисках нового...
	}
	// Изменяем счетчик анимации
	if(Counter<30) Counter++;
	else
	{
		Counter = 0;
		if (pAttUnit)
		{
			LookUp.LogMessage("Юнит атакует\n");
			if(Pos.i%2/*==1*/)OffSet=14;//нечет/чет
			else OffSet=0;
			if(pAttUnit->Pos.i%2/*==1*/)OffSet2=14;//нечет/чет
			else OffSet2=0;
			vx=(Pos.j*26+14+OffSet)-(pAttUnit->Pos.j*26+14+OffSet2);
			vy=(Pos.i*7-4)-(pAttUnit->Pos.i*7+12);
			//len=sqrt(vx*vx+vy*vy);
			if (sqrt(vx*vx+vy*vy)<=GetRad()){
				Fire();//Огонь!!!!
				if (pAttUnit&&pAttUnit->Whose!=CurRival&&pAttUnit->pAttUnit==NULL)//враг?
					pAttUnit->pAttUnit=this;//первый уровень искусвенного интилекта,однако:) 
			}
		}
		// Изменяем текущий кадр
		//Frame++; 
	}
	return TRUE; // Не уничтожать
} // Move() 

void tGunTurret::Fire()
{
	LookUp.LogMessage("Юнит стреляет\n");
	pUnit2=new tRocket(Pos,pAttUnit->Pos,MinDimage,MaxDimage);
	UnitList.push_front(pUnit2);
	/*
	pAttUnit->health+=BYTE((randint(MinDimage,MaxDimage))/ 
	            (randint(pAttUnit->MinDefend,pAttUnit->MaxDefend)));*/
	if(pAttUnit->health>=H_DEAD){
		pAttUnit=NULL;
		MessageMeAboutAllUnits(Pos);
		LookUp.LogMessage("Юнит убил...\n");
	}
}

void tGunTurret::Process(tUnit* pUnit)
{
	/*// на всякий случай…
	if(bDie) return;
	// Если другой объект – взрыв, дальнейшая обработка не нужна
	if(pUnit->GetType()==UNITTYPE_INFANTRY) return;
	// Если есть столкновение…
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// Взрывом задело объект типа “игрок”
			//case UNITTYPE_INFANTRY:
			//	pUnit->Kill(); // Убиваем игрока
			//break;
			default:
			break;
		} // switch
	} // if*/
} // Process()

BOOL tBarraks::Move()
{
	// Уничтожить?
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
	// Изменяем счетчик анимации
	if(Counter<30) Counter++;
	else
	{
		Counter = 0;
		// Изменяем текущий кадр
		//Frame++; 
	}
	return TRUE; // Не уничтожать
} // Move() 

void tBarraks::Process(tUnit* pUnit)
{
	/*// на всякий случай…
	if(bDie) return;
	// Если другой объект – взрыв, дальнейшая обработка не нужна
	if(pUnit->GetType()==UNITTYPE_INFANTRY) return;
	// Если есть столкновение…
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// Взрывом задело объект типа “игрок”
			//case UNITTYPE_INFANTRY:
			//	pUnit->Kill(); // Убиваем игрока
			//break;
			default:
			break;
		} // switch
	} // if*/
} // Process()

BOOL tExplosion::Move()
{
	// Уничтожить?
	if(bDie) return FALSE;
	// Изменяем счетчик анимации
	if(Counter < 2) Counter++; 
	else{
		Counter = 0;
		if(Frame < 8) // Изменяем текущий кадр
			Frame++;
		else
			return FALSE; // Уничтожить
	}
	return TRUE; // Не уничтожать
} // Move() 

void tExplosion::Process(tUnit* pUnit)
{
	// на всякий случай…
	if(bDie) return;
	// Если другой объект – взрыв, дальнейшая обработка не нужна
	if(pUnit->GetType()==UNITTYPE_MEXPLOSION) return;
	// Если есть столкновение…
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// Взрывом задело объект типа “игрок”
			case UNITTYPE_INFANTRY:
				pUnit->Kill(); // Убиваем игрока
			break;
			default:
			break;
		} // switch
	} // if
} // Process()

BOOL tRocket::Move()
{
	// Уничтожить?
	if(bDie) return FALSE;
	// Изменяем счетчик анимации
	/*if(Frame < 3){*/
		pr+=55;
		if (pr>=max_pr){
			pUnit2=new tExplosion(Target.y/7,Target.x/26,MinDimage,MaxDimage);
			UnitList.push_front(pUnit2);
			return FALSE;
		}
		// Изменяем текущий кадр
		Frame++;
	/*}
	else Frame=0;*/
	return TRUE; // Не уничтожать
} // Move() 

void tRocket::Process(tUnit* pUnit)
{
	// на всякий случай…
	if(bDie) return;
	// Если другой объект – взрыв, дальнейшая обработка не нужна
	if(pUnit->GetType()==UNITTYPE_MEXPLOSION) return;
	// Если есть столкновение…
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// Взрывом задело объект типа “игрок”
			case UNITTYPE_INFANTRY:
				pUnit->Kill(); // Убиваем игрока
			break;
			default:
			break;
		} // switch
	} // if
} // Process()

//ниже - две функции, отвечающие за 2 уровень И.И.
void MessageAllUnitsAboutMe(INDEX pos){
	const MaxSight=1500;
	for(tUnitListIterator UnitLI=UnitList.begin();UnitLI!=UnitList.end();UnitLI++)
	{
		pUnit2=*UnitLI;
		//если емеем дело с самим сабой или с "земляком",то информировать не надо 
		if (pUnit2==Field[pos.i][pos.j]->pUnit||pUnit2->Whose==CurRival||pUnit2->health>=H_DEAD
			) continue;
		if(pos.i%2/*==1*/)OffSet2=14;//нечет/чет
		else OffSet2=0;
		int xp=pos.j*26+OffSet2;
		int yp=pos.i*7;
		if(pUnit2->Pos.i%2/*==1*/)OffSet2=14;//нечет/чет
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
		//если емеем дело с самим сабой или с "земляком" или с трупом,то обробатывать не надо 
		if (pUnit2==Field[pos.i][pos.j]->pUnit||pUnit2->Whose==CurRival||pUnit2->health>=H_DEAD) continue;
		if(pos.i%2/*==1*/)OffSet2=14;//нечет/чет
		else OffSet2=0;
		int xp=pos.j*26+OffSet2;
		int yp=pos.i*7;
		if(pUnit2->Pos.i%2/*==1*/)OffSet2=14;//нечет/чет
		else OffSet2=0;
		int xd=pUnit2->Pos.j*26+OffSet2;
		int yd=pUnit2->Pos.i*7;
		int absxo=0;
		int absyo=0;
		if (Field[pos.i][pos.j]->pUnit->pAttUnit){
			if(Field[pos.i][pos.j]->pUnit->pAttUnit->Pos.i%2/*==1*/)OffSet2=14;//нечет/чет
    		else OffSet2=0;
	    	int xa=Field[pos.i][pos.j]->pUnit->pAttUnit->Pos.j*26+OffSet2;
    		int ya=Field[pos.i][pos.j]->pUnit->pAttUnit->Pos.i*7;
			absxo=abs(xp-xa);//absx[old]-расстояние до старого врага
		    absyo=abs(yp-ya);//absy[old]
		}
		int absxn=abs(xp-xd);//absx[new]-расстояние до возможно будущего врага 
		int absyn=abs(yp-yd);//absy[new]
		if (absxn<=MaxSight&&absyn<=MaxSight)
			if (Field[pos.i][pos.j]->pUnit->PathList.empty()&&
				(!Field[pos.i][pos.j]->pUnit->pAttUnit||
				Field[pos.i][pos.j]->pUnit->pAttUnit&&(absxn<absxo&&absyn<absyo)))
				Field[pos.i][pos.j]->pUnit->pAttUnit=pUnit2;
	}
}