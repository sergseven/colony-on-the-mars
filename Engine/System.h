////////////////////////////////////////////////////////////
//
//Модуль системных функций движка.
//
////////////////////////////////////////////////////////////

#include "Init.h"

void tEngine::RunEngine(int MSI,int MSJ)
{
	MSG msg;//сообщения
    try
    {
		MapSizeI=MSI;
		MapSizeJ=MSJ;
		ScrlI = 0;//MapSizeI-MapSizeI/2-41;//ДОЛЖНО БЫТЬ КРАТНО ДВУМ!!! 
		ScrlJ = 0;//MapSizeJ-MapSizeJ/2-20;//
		InitGame();
		tFile::LogMessage("InitGame Thread Complite\n");
		tDirectInput::Activate();
		while(1)
		if(PeekMessage (&msg,NULL,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&msg,NULL,0,0)) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else
			//// Запуск задачи
            (*m_thread)();
    tFile::LogMessage("Quit doing.....");
    }
    catch(tError &error)
    {
        error.AddErrorHistory(" <-tEngine::RunEngine <-tEngine.dll");
        throw;
    }

}

void tEngine::ProcessMsg()
{
	int RectX,RectY; 
	//bool bNotBuilding=false;
	if (mx>14&&mx<783&&my>23&&my<423)
	{
		TileI = (my-24)/14;
		sprintf(tstr1,"посл таил и = %d",TileI);
		TileJ = (mx-15)/28;
		sprintf(tstr2,"посл таил й = %d",TileJ);
		RectX = (mx-15)%28;
		RectY = (my-24)%14;
		switch (Mask[RectY][RectX])
		{
			case 0: TileI=TileI*2+1;
				sprintf(tstr3,"кейс 0");
			break;
			case 1: TileI=TileI*2;
				sprintf(tstr3,"кейс 1");
	   		break;
	    	case 2: TileI=TileI*2+2;
					sprintf(tstr3,"кейс 3");
			break;
			case 3: TileI=TileI*2;
				    TileJ=TileJ+1;
					sprintf(tstr3,"кейс 2");
			break;
			case 4: TileI=TileI*2+2;
	 			    TileJ=TileJ+1;
					sprintf(tstr3,"кейс 4");
			break;
		}
		if (pLB) 
		{
			TotalAU=0;
			UnitLI=AUnitList.begin();
			while (UnitLI!=AUnitList.end())
			{
				//LogMessage("deleting el. of AUL\n");
				pUnit=*UnitLI;
				pUnit->Alloted=FALSE;
				UnitLI = AUnitList.erase(UnitLI);  
			}
			RectLI=RectList.begin();
			while (RectLI!=RectList.end()){
				//LogMessage("run clear list \n");
				pRect=*RectLI;
				delete pRect;
				RectLI = RectList.erase(RectLI);
			}
			if (cLB){
				FirstC.x=mx;
				FirstC.y=my;
			}
			if (FirstC.x<=mx&&FirstC.y<=my){
				DEBar(FirstC.x-1,FirstC.y-1,mx-FirstC.x,my-FirstC.y,0);
				for(RectUnitLI=RectUnitList.begin();RectUnitLI!=RectUnitList.end()&&TotalAU<=24;RectUnitLI++){
					pRectUnit=*RectUnitLI;
					if ((FirstC.y<=pRectUnit->Rect.bottom&&
						 my>=pRectUnit->Rect.top)&&
						(FirstC.x<=pRectUnit->Rect.right&&
						 mx>=pRectUnit->Rect.left)&&
						pRectUnit->pUnit->Whose==CurRival)
					{
						AUnitList.push_back(pRectUnit->pUnit); 
						pRectUnit->pUnit->Alloted=TRUE;
						TotalAU++;
						//bNotBuilding=true;
					}
				}
			}
			else
			if (FirstC.x<mx&&FirstC.y>my){
				DEBar(FirstC.x-1,my,mx-FirstC.x,FirstC.y-my,0);
				for(RectUnitLI=RectUnitList.begin();RectUnitLI!=RectUnitList.end()&&TotalAU<=24;RectUnitLI++){
					pRectUnit=*RectUnitLI;
					if ((FirstC.y>=pRectUnit->Rect.top&&
						 my<=pRectUnit->Rect.bottom)&&
						(FirstC.x<=pRectUnit->Rect.right&&
						 mx>=pRectUnit->Rect.left)&&
						pRectUnit->pUnit->Whose==CurRival)
					{
						AUnitList.push_back(pRectUnit->pUnit); 
						pRectUnit->pUnit->Alloted=TRUE;
						TotalAU++;
						//bNotBuilding=true;
					}
				}
			}
			else
			if (FirstC.x>mx&&FirstC.y<my){
				DEBar(mx,FirstC.y-1,FirstC.x-mx,my-FirstC.y,0);
				for(RectUnitLI=RectUnitList.begin();RectUnitLI!=RectUnitList.end()&&TotalAU<=24;RectUnitLI++){
					pRectUnit=*RectUnitLI;
					if ((FirstC.y<=pRectUnit->Rect.bottom&&
						 my>=pRectUnit->Rect.top)&&
						(FirstC.x>=pRectUnit->Rect.left&&
						 mx<=pRectUnit->Rect.right)&&
						pRectUnit->pUnit->Whose==CurRival)
					{
						AUnitList.push_back(pRectUnit->pUnit); 
						pRectUnit->pUnit->Alloted=TRUE;
						TotalAU++;
						//bNotBuilding=true;
					}
				}
			}
			else
			if (FirstC.x>mx&&FirstC.y>my){
				DEBar(mx,my,FirstC.x-mx,FirstC.y-my,0);
				for(RectUnitLI=RectUnitList.begin();RectUnitLI!=RectUnitList.end()&&TotalAU<=24;RectUnitLI++){
					pRectUnit=*RectUnitLI;
					if ((FirstC.y>=pRectUnit->Rect.top&&
						 my<=pRectUnit->Rect.bottom)&&
						(FirstC.x>=pRectUnit->Rect.left&&
						 mx<=pRectUnit->Rect.right)&&
						pRectUnit->pUnit->Whose==CurRival)
					{
						AUnitList.push_back(pRectUnit->pUnit); 
						pRectUnit->pUnit->Alloted=TRUE;
						TotalAU++;
						//bNotBuilding=true;
					}
				}		
			}
			if (/*bNotBuilding==false&&*/
				Field[TileI+ScrlI][TileJ+ScrlJ]->pUnit&&
				Field[TileI+ScrlI][TileJ+ScrlJ]->pUnit->bBuilding)
			{
				AUnitList.push_back(Field[TileI+ScrlI][TileJ+ScrlJ]->pUnit);  
				Field[TileI+ScrlI][TileJ+ScrlJ]->pUnit->Alloted=TRUE;
				TotalAU++;
			}/*
			for(RectUnitLI=RectUnitList.begin();RectUnitLI!=RectUnitList.end();RectUnitLI++)
			{
				pRectUnit=*RectUnitLI;
				//LogMessage("Run for: left=%d right=%d bottom=%d top=%d i=%d j=%d\n",pRectUnit->Rect.left,pRectUnit->Rect.right,pRectUnit->Rect.bottom,pRectUnit->Rect.top,pRectUnit->pUnit->Pos.i,pRectUnit->pUnit->Pos.j);
				if (mx>=pRectUnit->Rect.left&&
					mx<=pRectUnit->Rect.right&&
					my>=pRectUnit->Rect.top&&
					my<=pRectUnit->Rect.bottom&&
					pRectUnit->pUnit->Whose==CurRival)
				{
					LogMessage("Infantry Alloted \n");
					AUnitList.push_back(pRectUnit->pUnit);  
					pRectUnit->pUnit->Alloted=TRUE;
				}
			}*/
		}else
		if (cRB)
		{
			for(RectUnitLI=RectUnitList.begin();RectUnitLI!=RectUnitList.end();RectUnitLI++)
			{//проверяем все зоны
				pRectUnit=*RectUnitLI;
				//LogMessage("Run for: left=%d right=%d bottom=%d top=%d i=%d j=%d\n",pRectUnit->Rect.left,pRectUnit->Rect.right,pRectUnit->Rect.bottom,pRectUnit->Rect.top,pRectUnit->pUnit->Pos.i,pRectUnit->pUnit->Pos.j);
				if (mx>=pRectUnit->Rect.left&&
					mx<=pRectUnit->Rect.right&&
					my>=pRectUnit->Rect.top&&
					my<=pRectUnit->Rect.bottom&&
					pRectUnit->pUnit->Whose!=CurRival)//враг?
				{
					LogMessage("Units Attack\n");
					pUnit=NULL;
					for(UnitLI=AUnitList.begin();UnitLI!=AUnitList.end();UnitLI++)
					{
						pUnit=*UnitLI;
						pUnit->pAttUnit=pRectUnit->pUnit;
					}
					if (pUnit) return;//если были выделенные 
				}
			}
			Field[TileI+ScrlI][TileJ+ScrlJ]->nSprt = 1; 
			for(UnitLI=AUnitList.begin();UnitLI!=AUnitList.end();UnitLI++)
			{
				pUnit=*UnitLI;
				if (!pUnit->bBuilding){
					pUnit->Action.i=TileI+ScrlI;
					pUnit->Action.j=TileJ+ScrlJ;
					pUnit->pAttUnit=NULL;
					pUnit->PathList.clear();
					LookUp.LogMessage("...........................\n");
				}
			}
		}
	}
	else
	{

		if (mx<=7&&ScrlJ) ScrlJ--;
		if (my<=7&&ScrlI) ScrlI-=2;
		if (mx>=MaxX-CursorLengthX-5&&ScrlJ!=MapSizeJ-ViewedMapSizeJ) ScrlJ++;
		if (my>=MaxY-CursorLengthY-5&&ScrlI!=MapSizeI-ViewedMapSizeI-1) ScrlI+=2;
		if (cLB){
			for(RectLI=RectList.begin();RectLI!=RectList.end();RectLI++){
				    pRect=*RectLI;
					if ((my<=pRect->Rect.bottom&&
						 my>=pRect->Rect.top)&&
						(mx<=pRect->Rect.right&&
						 mx>=pRect->Rect.left))
					{
						if (pRect->ThreadInd){
							pRect->pUnit->ThreadInd=pRect->ThreadInd;
							pRect->pUnit->Complite=0;
							return;
						}

						TotalAU=0;
						UnitLI=AUnitList.begin();
						while (UnitLI!=AUnitList.end()){
							//LogMessage("deleting el. of AUL\n");
							pUnit=*UnitLI;
							pUnit->Alloted=FALSE;
							UnitLI = AUnitList.erase(UnitLI);  
						}
						AUnitList.push_back(pRect->pUnit); 
						pRect->pUnit->Alloted=TRUE;
						TotalAU++;
					}
			}

		}
	}
			/*if (Field[i][j]->pUnit!=NULL)
					Field[i][j]->pUnit->Alloted = TRUE;*/
		/*for (i=0;i<MapSizeI;i++)
		for (j=0;j<MapSizeJ;j++)
		{
			if ((i%2)==1) OffSet=13;
			else          OffSet=0;
			if (Abs(Abs((mx-(j*16+8+OffSet))/27)+Abs(my-(i*4+20)))<=3)
				if (Field[i][j]->pUnit!=NULL)
					Field[i][j]->pUnit->Alloted = TRUE;
			
		}*/
}

void tEngine::Update(void)
{
	try
	{
		time=GetTickCount();
		LookUp.LogMessage("run Update Thread\n");
		RectUnitLI=RectUnitList.begin();
		while (RectUnitLI!=RectUnitList.end())
		{
			//LogMessage("run clear list \n");
			pRectUnit=*RectUnitLI;
			delete pRectUnit;
			RectUnitLI = RectUnitList.erase(RectUnitLI);
		}
		time1=GetTickCount()-time;
		for (i=0;i<ViewedMapSizeI;i++){
			if(i%2/*==1*/)OffSet=14;//нечет/чет
			else OffSet=0;
		for (j=0;j<ViewedMapSizeJ;j++)
		{
			SetR(rect,Field[i+ScrlI][j+ScrlJ]->nSprt*26,0,26,14);
			/*switch (Field[i+ScrlI][j+ScrlJ]->nSprt)
			{
			case 1:SetR(rect,0,0,26,14);
			break;
			case 2:SetR(rect,26,0,26,14);
			break;
			case 3:SetR(rect,52,0,26,14);
			break;
			case 4:SetR(rect,78,0,26,14);
			break;
			}*/
			//LookUp.LogMessage("run tile draw\n");
			BlitImage(Mulx26p2[j]+OffSet,Mulx7p17[i],nABGSurf,&rect);
			if (Field[i+ScrlI][j+ScrlJ]->pUnit!=NULL)
				switch (Field[i+ScrlI][j+ScrlJ]->pUnit->GetType())
				{
				case UNITTYPE_INFANTRY:
					//LogMessage("run new rect in xp=%d yp=%d, i=%d j=%d\n",(j*16+8)+OffSet,i*4+12,i+ScrlI,j+ScrlJ);
					pRectUnit = new tRectUnit((Mulx26[j]+6)+OffSet/*+OffSet3.x*/,
						               Mulx7[i]/*+OffSet3.y*/,12,25,
									   Field[i+ScrlI][j+ScrlJ]->pUnit);
					RectUnitList.push_back(pRectUnit);  
					/*SetR(rect,Field[i+ScrlI][j+ScrlJ]->pUnit->Frame*33+1,0,32,32);
					BlitImage(Mulx26[j]-2+OffSet+Field[i+ScrlI][j+ScrlJ]->pUnit->OSx,
						Mulx7[i]-4+Field[i+ScrlI][j+ScrlJ]->pUnit->OSy,nASSurf,&rect);*/
       			break;
				case UNITTYPE_TURRET:
					//LogMessage("run TURR");
					if (Field[i+ScrlI][j+ScrlJ]->pUnit->Pos.i==(i+ScrlI)&&
						Field[i+ScrlI][j+ScrlJ]->pUnit->Pos.j==(j+ScrlJ))
					{
						//LogMessage("run blt TURR");
						pRectUnit = new tRectUnit(0,0,0,0,Field[i+ScrlI][j+ScrlJ]->pUnit);
						RectUnitList.push_back(pRectUnit);  
					}
				break;
				case UNITTYPE_BARRAKS:
					//LogMessage("run Barr");
					if (Field[i+ScrlI][j+ScrlJ]->pUnit->Pos.i==(i+ScrlI)&&
						Field[i+ScrlI][j+ScrlJ]->pUnit->Pos.j==(j+ScrlJ))
					{
						//LogMessage("run blt BARR");
						pRectUnit = new tRectUnit(0,0,0,0,Field[i+ScrlI][j+ScrlJ]->pUnit);
						RectUnitList.push_back(pRectUnit);  
					}
				break;
				case UNITTYPE_UNIT:
				default:
				break;
				}
		}}
		time2=GetTickCount()-time1-time;
		//time3=time2/ViewedMapSizeI;//время каждой i-той итерации
		//time4=time3/ViewedMapSizeJ;//время каждой j-той итерации
		for(RectUnitLI=RectUnitList.begin();RectUnitLI!=RectUnitList.end();RectUnitLI++)
		{
		//	LookUp.LogMessage("run draw rect\n");
			pRectUnit=*RectUnitLI;
			if ((pRectUnit->pUnit->Pos.i-ScrlI)%2/*==1*/) OffSet=14;//нечет/чет
			else OffSet = 0;
			switch (pRectUnit->pUnit->GetType())
			{
			case UNITTYPE_INFANTRY:
			//	LookUp.LogMessage("run Infantry");
					/*angle=GetAngle(i+ScrlI,j+ScrlJ,
					Field[i+ScrlI][j+ScrlJ]->pUnit->Action.i,
					Field[i+ScrlI][j+ScrlJ]->pUnit->Action.j);
	    			LogMessage("ang=%d",angle);*///для танков,пушек,с вращающейся башней
		    		//LogMessage("run new rect in xp=%d yp=%d, i=%d j=%d\n",(j*16+8)+OffSet,i*4+12,i+ScrlI,j+ScrlJ);
				SetR(rect,pRectUnit->pUnit->Frame*33+1,0,32,32);
				BlitImage(Mulx26[pRectUnit->pUnit->Pos.j-ScrlJ]-2+OffSet+pRectUnit->pUnit->OSx,
					Mulx7[pRectUnit->pUnit->Pos.i-ScrlI]-4+pRectUnit->pUnit->OSy,nASSurf,&rect);
				
   			break;
			case UNITTYPE_TURRET:
			//	LogMessage("run TURR");
				SetR(rect,1,33,53,28);
				BlitImage(Mulx26[pRectUnit->pUnit->Pos.j-ScrlJ]-12+OffSet,
					      Mulx7[pRectUnit->pUnit->Pos.i-ScrlI]+3/*14*/,nASSurf,&rect);
			break;
			case UNITTYPE_BARRAKS:
				//LogMessage("run BARR");
				SetR(rect,101,0,53,58);
				BlitImage(Mulx26[pRectUnit->pUnit->Pos.j-ScrlJ]-12+OffSet,
					      Mulx7[pRectUnit->pUnit->Pos.i-ScrlI]-27/*14*/,nASSurf,&rect);
			break;
			default:
				LookUp.LogMessage("run default\n");
			break;
			}
			if (pRectUnit->pUnit->Alloted)
			{
			//LogMessage("run ual\n");
				LookUp.LogMessage("Юнит OSx=%d OSy=%d Fr=%d\n",pRectUnit->pUnit->OSx,pRectUnit->pUnit->OSy,pRectUnit->pUnit->Frame);
				SetR(rect,0,0,16,16);
				BlitImage((Mulx26[pRectUnit->pUnit->Pos.j-ScrlJ]+7)+pRectUnit->pUnit->OSx+OffSet,
					Mulx7[pRectUnit->pUnit->Pos.i-ScrlI]+pRectUnit->pUnit->OSy+6,nPic0Surf,&rect);
			}
		} 
		//вывод взрывов,снарядов и прочей мелкой перемещающейся швали
		//LogMessage("run rockets draw\n");
		UnitLI = UnitList.begin(); // Настраиваемся на первый элемент…
		// Для всех элементов…
		while(UnitLI!=UnitList.end())
		{
			pUnit=*UnitLI;
			switch (pUnit->GetType())
			{
			case UNITTYPE_MEXPLOSION:
				if (pUnit->Pos.i>=ScrlI&&pUnit->Pos.i<=ScrlI+ViewedMapSizeI&&
					pUnit->Pos.j>=ScrlJ&&pUnit->Pos.j<=ScrlJ+ViewedMapSizeJ){
					//LogMessage("run blt MEXPLOSION,OSx=%d OSy=%d\n",pUnit->OSx,pUnit->OSy);
					if(pUnit->Pos.i%2/*==1*/)OffSet=14;//нечет/чет
					else OffSet=0;
					SetR(rect,pUnit->Frame*54,0,54,54);
					BlitImage(Mulx26[pUnit->Pos.j-ScrlJ]-12+OffSet+pUnit->OSx,
						      Mulx7[pUnit->Pos.i-ScrlI]-8/*14*/+pUnit->OSy,nAESurf,&rect);
				}
			break;
			case UNITTYPE_ROCKET:
				//LogMessage("run rocket draw...");
				int vxS=Mulx26[ScrlJ]-13;//Scrl*
				int vyS=Mulx7[ScrlI]-7;
				int vxV=Mulx26[ScrlJ+ViewedMapSizeJ]+26;//Viewed+Scrl*
				int vyV=Mulx7[ScrlI+ViewedMapSizeI]+14;
				int xpr=pUnit->pr*pUnit->xpr_temple;
				int ypr=pUnit->pr*pUnit->ypr_temple;
				pUnit->OSx=pUnit->Start.x+xpr;
				pUnit->OSy=pUnit->Start.y+ypr;
				//LogMessage("vxS=%d vyS=%d vxV=%d vyV=%d xpr=%d ypr=%d pUnit->OSx=%d pUnit->OSy=%d pUnit->pr=%d\n",vxS,vyS,vxV,vyV,xpr,ypr,pUnit->OSx,pUnit->OSy,pUnit->pr);
				if (vxS<pUnit->OSx&&vyS<pUnit->OSy&&
					vxV>pUnit->OSx&&vyV>pUnit->OSy){
					//LogMessage("rocket drawing...\n");
					SetR(rect,0,54,16,16);
					BlitImage(pUnit->OSx-Mulx26[ScrlJ]+24,pUnit->OSy-Mulx7[ScrlI]+15,nAESurf,&rect);
				}
			break;
			}
			UnitLI++; // Следующий элемент
		} // while
		time3=GetTickCount()-time2-time1-time;
		SetRect(&rect,0,0,MaxX,MaxY);
		BlitImage(0,0,nIWSurf,&rect);
		if (TotalAU)
			if (TotalAU>=2){
				BYTE C=0;//Counter
				UnitLI=AUnitList.begin();
				while (UnitLI!=AUnitList.end()){
					pUnit=*UnitLI;
					if (pUnit->bDie||pUnit->health>=H_DEAD){
						UnitLI = AUnitList.erase(UnitLI);
						TotalAU--;
						continue;
					}
					C++;
					pRect = new tRect(250+((C-1)%8)*45,460+((C-1)/8)*45,FaceLengthX,FaceLengthY,pUnit);
					pRect->ThreadInd=0;
					RectList.push_back(pRect);  
					BlitImage(250+((C-1)%8)*45,460+((C-1)/8)*45,nUnitFotosSurf,&pUnit->rFoto);
					UnitLI++;
				}
			}
			else{
				LogMessage("TAU>0&&TAU<2------>TAU=1");
				pUnit=*AUnitList.begin();
				if (pUnit->bDie||pUnit->health>=H_DEAD){
					AUnitList.erase(AUnitList.begin());
					TotalAU--;
				}
				else{
					if (pUnit->bBuilding&&
						 pUnit->GetType()==UNITTYPE_BARRAKS){
						 pRect = new tRect(15,460,FaceLengthX,FaceLengthY,pUnit);
    					pRect->ThreadInd=UNITTYPE_INFANTRY;
     					RectList.push_back(pRect); 
    					BlitImage(15,460,nUnitFotosSurf,&pUnit->rFoto);
					}
    				BlitImage(250,460,nUnitFotosSurf,&pUnit->rFoto);
    				sprintf(tstr4,"навык атаки:%d",pUnit->MinDimage); 
    				BlitString(300,460,tstr4,nFontCGwSurf);
    				sprintf(tstr4,"сила оружия:%d",pUnit->MaxDimage); 
    				BlitString(300,475,tstr4,nFontCGwSurf);
	    			sprintf(tstr4,"навык защиты:%d",pUnit->MinDefend); 
	    			BlitString(300,490,tstr4,nFontCGwSurf);
	    			sprintf(tstr4,"сила защиты:%d",pUnit->MaxDefend); 
	    			BlitString(300,505,tstr4,nFontCGwSurf);
				}
			}
		sprintf(tstr4,"(и=%d й=%d)",TileI+ScrlI,TileJ+ScrlJ); 
		BlitString(20,30,tstr4,nFontCGwSurf);
		BlitString(20,45,tstr1,nFontCGwSurf);
		BlitString(20,60,tstr2,nFontCGwSurf);
		BlitString(20,75,tstr3,nFontCGwSurf);
		sprintf(tstr4,"мх:%d му:%d ",mx,my); 
		BlitString(20,90,tstr4,nFontCGwSurf);
		if (Flips==3)
		{
			timethen=timenow;
			timenow=timeGetTime();
			seconds=double(timenow-timethen)/(double)1000;
			FPS=(int)((double)Flips/seconds);
			Flips=0;
		}
		sprintf(tstr4,"квс = %d",FPS); 
		BlitString(20,105,tstr4,nFontCGwSurf);
		//времечко
		sprintf(tstr4,"время=%d",time); 
		BlitString(20,135,tstr4,nFontCGwSurf);
		sprintf(tstr4,"время1=%d",time1); 
		BlitString(20,150,tstr4,nFontCGwSurf);
		sprintf(tstr4,"время2=%d",time2); 
		//LogMessage(tstr4);
		BlitString(20,165,tstr4,nFontCGwSurf);
		sprintf(tstr4,"время3=%d",time3);
		//LogMessage(tstr4);
		BlitString(20,180,tstr4,nFontCGwSurf);
		sprintf(tstr4,"время4=%d",time4);
		//LogMessage(tstr4);
		BlitString(20,195,tstr4,nFontCGwSurf);
		sprintf(tstr4,"время5=%d",time5); 
		BlitString(20,210,tstr4,nFontCGwSurf);
		sprintf(tstr4,"время6=%d",time6); 
		//LogMessage(tstr4);
		BlitString(20,225,tstr4,nFontCGwSurf);
		sprintf(tstr4,"время7=%d",time7); 
		//LogMessage(tstr4);
		BlitString(20,240,tstr4,nFontCGwSurf);
		//sprintf(tstr4,"время8=%d",time8); 
		//BlitString(20,MaxY-60,tstr4,nFontCGwSurf);
		//sprintf(tstr4,"время9=%d",time9); 
		//BlitString(20,MaxY-45,tstr4,nFontCGwSurf);
		//sprintf(tstr4,"время10=%d",time10); 
		//BlitString(20,MaxY-30,tstr4,nFontCGwSurf);
/*
		for (i = 0;i<MapSizeI;i++)
		for (j = 0;j<MapSizeJ;j++)
		{
			//LogMessage("run For \n");
			switch (Field[i][j]->nSprt)
			{
			case 1:SetR(rect,x_grnd1,y_grnd1,x_grnd_length,y_grnd_length);
			break;
			case 2:SetR(rect,x_grnd2,y_grnd2,x_grnd_length,y_grnd_length);
			break;
		    case 3:SetR(rect,x_grnd3,y_grnd3,x_grnd_length,y_grnd_length);
			break;
		    case 4:SetR(rect,x_grnd4,y_grnd4,x_grnd_length,y_grnd_length);
			//	engine->LogMessage("run For case 4\n");
			break;
			case 5:SetR(rect,x_grnd5,y_grnd5,x_grnd_length,y_grnd_length);
			break;
			case 6:SetR(rect,x_grnd6,y_grnd6,x_grnd_length,y_grnd_length);
			break;
			case 7:SetR(rect,x_grnd7,y_grnd7,x_grnd_length,y_grnd_length);
			break;
			case 8:SetR(rect,x_grnd8,y_grnd8,x_grnd_length,y_grnd_length);			
			//	engine->LogMessage("run For case 8\n");
			break;
			case 9:SetR(rect,x_grnd9,y_grnd9,x_grnd_length,y_grnd_length);
			break;
			case 10:SetR(rect,x_grnd10,y_grnd10,x_grnd_length,y_grnd_length);
			break;
			case 11:SetR(rect,x_grnd11,y_grnd11,x_grnd_length,y_grnd_length);
			break;
			case 12:SetR(rect,x_grnd12,y_grnd12,x_grnd_length,y_grnd_length);
			//	engine->LogMessage("run For case 12\n");
			break;
			case 13:SetR(rect,x_grnd13,y_grnd13,x_grnd_length,y_grnd_length);
			break;
			case 14:SetR(rect,x_grnd14,y_grnd14,x_grnd_length,y_grnd_length);
			break;
			case 15:SetR(rect,x_grnd15,y_grnd15,x_grnd_length,y_grnd_length);
			break;
			case 16:SetR(rect,x_grnd16,y_grnd16,x_grnd_length,y_grnd_length);
				engine->LogMessage("run For case 16\n");
			break;
			}
			BlitImage(i*16+15,j*16+24,nABGSurf,&rect);
			if (Field[i][j]->pUnit!=NULL)
				switch (Field[i][j]->pUnit->GetType())
				{
				case UNITTYPE_INFANTRY:
					SetR(rect,0,0,16,16);
					engine->BlitImage(j*16+15,i*16+24,nASSurf,&rect);
				break;
				case UNITTYPE_UNIT:
				default:
				break;
				}
		}*/
		//engine->LogMessage("run Part 1\n");
		// Часть 1 – обработка внутренних данных, и т.д.
		UnitLI = UnitList.begin(); // Настраиваемся на первый элемент…
		// Для всех элементов…
		int tRival=CurRival;
		while(UnitLI!=UnitList.end())
		{
			pUnit=*UnitLI;
			CurRival=pUnit->Whose;
			if(!pUnit->Move()) // Объект просит себя уничтожить?
			{
				delete pUnit; // Удаляем объект 
				// Удаляем элемент списка и получаем следующий
				UnitLI = UnitList.erase(UnitLI); 
			}
			else UnitLI++; // Следующий элемент
		} // while
		CurRival=tRival;
		time4=GetTickCount()-time3-time2-time1-time;

		//engine->LogMessage("run Part 2\n");

		// Часть 2 - обработка взаимодействия
		/*UnitLI = UnitList.begin();
		while(UnitLI != UnitList.end())
		{
			pUnit=*UnitLI;
			UnitLI2 = UnitList.begin();
			while(UnitLI2 != UnitList.end())
			{
				pUnit2 = *UnitLI2;
				// Проверяем…
				if(pUnit && pUnit2 && pUnit != pUnit2)
					pUnit->Process(pUnit2); // И обрабатываем
				UnitLI2++;
			} // while
			UnitLI++;
		} // while*/
		/*for(UnitLI=UnitList.begin(); UnitLI != UnitList.end();UnitLI++)
		{
			pUnit=*UnitLI;
			pUnit->Blit();
		} */
		LookUp.LogMessage("FPS=%d\n",FPS);
		DrawScene();   //Вывод курсора мышки
		ProcessMsg();  //Обработка сообщений от мышки 
		FlipSurfaces();//выполняет переключение поверхностей
		Flips++;
		time5=GetTickCount()-time4-time3-time2-time1-time;
		//SetEngineThread(Null);
    }
    catch(tError &error)
    {
        error.AddErrorHistory(" <-tEngine::Update <-tEngine.dll");
        throw;
    }
}
