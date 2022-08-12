#include "stdio.h"
#include "string.h"

main()
{float totaldays;
 int weekday,employees,rest,altoff,firstday,n=0,date,i,j,changeshift=0,free[31],gen[31],mor[31],eve[31],k,GME_employees,G_employees;
 char rotatable[20][31],employeename[20][100],sfirstday[4],srest[4],prefshift[20],shiftvar;
 FILE *fp,*fp1;
 
 fp1=fopen("ROTA_input.txt","r");
 fscanf(fp1,"%f %s",&totaldays,&sfirstday);
 
 if(strcmp("SUN",sfirstday)==0) firstday=1;
 else if(strcmp("MON",sfirstday)==0) firstday=2;
 else if(strcmp("TUE",sfirstday)==0) firstday=3;
 else if(strcmp("WED",sfirstday)==0) firstday=4;
 else if(strcmp("THU",sfirstday)==0) firstday=5;
 else if(strcmp("FRI",sfirstday)==0) firstday=6;
 else if(strcmp("SAT",sfirstday)==0) firstday=7;

 weekday=firstday;

 fp=fopen("ROTA_planned_by_SATISH_KUSHWAH.csv","w+");
 for ( i = 0; i < totaldays; i++)
		 { fprintf(fp,",%d",i+1);
		   free[i]=0; gen[i]=0; mor[i]=0; eve[i]=0;
		 }
 fprintf(fp,"\n");
 for ( i = 0; i < totaldays; i++)
  { if(weekday>7)
  	  weekday=1;
  	  switch(weekday)
  	   { case 1: fprintf(fp,",SUN"); break;
  	     case 2: fprintf(fp,",MON"); break;
  	     case 3: fprintf(fp,",TUE"); break;
  	     case 4: fprintf(fp,",WED"); break;
  	     case 5: fprintf(fp,",THU"); break;
  	     case 6: fprintf(fp,",FRI"); break;
  	     case 7: fprintf(fp,",SAT"); break;
        }
      weekday=weekday+1;
  }
fprintf(fp,"\n");
fscanf(fp1,"%d %d",&GME_employees,&G_employees);
for (i = 0; i < (GME_employees+G_employees); i++)
for (j = 0; j < totaldays; j++)
		rotatable[i][j]='F'; 

for( i=0;i<(GME_employees+G_employees);i++)
  {    fscanf(fp1,"%s %s %d %c",&employeename[i],&srest,&altoff,&prefshift[i]);             
      
         if(strcmp("SUN",srest)==0) rest=1;
		 else if(strcmp("MON",srest)==0) rest=2;
		 else if(strcmp("TUE",srest)==0) rest=3;
		 else if(strcmp("WED",srest)==0) rest=4;
		 else if(strcmp("THU",srest)==0) rest=5;
		 else if(strcmp("FRI",srest)==0) rest=6;
		 else if(strcmp("SAT",srest)==0) rest=7;

	     while(1)
	             {date=1+7*n+rest-firstday;
	              if(date>totaldays) break; 
	              if(date>0)
	                 {rotatable[i][date-1]='R'; }
	              n++;
	             }
	             n=0;
	     if((rest-1)<firstday)
	     	{ if(altoff==1)
	     		 {date=1+7+(rest-1)-firstday;
	              rotatable[i][date-1]='A'; 
	              date=1+7*3+(rest-1)-firstday;
	              rotatable[i][date-1]='A'; 
	             }
	          else if(altoff==2)
	              {date=1+7*2+(rest-1)-firstday;
	              rotatable[i][date-1]='A'; 
	              date=1+7*4+(rest-1)-firstday;
	              rotatable[i][date-1]='A'; 
	              }
	      
	        }
	      else { if(altoff==1)
		     		 {date=1+(rest-1)-firstday;
		              rotatable[i][date-1]='A'; 
		         	  date=1+7*2+(rest-1)-firstday;
		              rotatable[i][date-1]='A'; 
		             }
	             else if(altoff==2)
		              {date=1+7*1+(rest-1)-firstday;
		              rotatable[i][date-1]='A'; 
		              date=1+7*3+(rest-1)-firstday;
		              rotatable[i][date-1]='A'; 
		              }
	            }
  }
	for(j=0;j<GME_employees;j++) 
    for(k=0;k<totaldays;k++) 
		if(rotatable[j][k]=='F') free[k]++;
	
 for(i=0;i<GME_employees;i++)
   {   shiftvar=prefshift[i]; 
   	for(j=0;j<totaldays;j++) 
        { if(rotatable[i][j]=='F') 
	              {changeshift=1;
		              	if(shiftvar=='G') 
		              	     { if((free[j]+mor[j]+eve[j])>4) { rotatable[i][j]='G'; gen[j]++; free[j]--; }      
		                       else if(mor[j]<2) { rotatable[i][j]='M'; mor[j]++; free[j]--; }
		                       else { rotatable[i][j]='E'; eve[j]++; free[j]--; }         
		                     }
		                else if(shiftvar=='M') 
		                	 { if(mor[j]<2) {rotatable[i][j]='M'; mor[j]++; free[j]--;}
                               else if(eve[j]<2)  {rotatable[i][j]='E'; eve[j]++; free[j]--;  }
                               else {rotatable[i][j]='G'; gen[j]++; free[j]--; }
		                	 }
		                else if(shiftvar=='E')	
		                     { if(eve[j]<2) {rotatable[i][j]='E'; eve[j]++; free[j]--; }
                               else if((free[j]+mor[j]+eve[j])>4) { rotatable[i][j]='G'; gen[j]++; free[j]--; }  
                               else {rotatable[i][j]='M'; mor[j]++; free[j]--; }
		                     }
	              }
           else if(rotatable[i][j]=='R') 
	           	  { if(changeshift==1)  { if(shiftvar=='G') shiftvar='M';
                                          else if(shiftvar=='M') shiftvar='E';
                                          else if(shiftvar=='E') shiftvar='G';
	                                    }
	           	  }
        }  
        changeshift=0;
   }

   for(i=GME_employees;i<(GME_employees+G_employees);i++)
   for(j=0;j<totaldays;j++)
   	  if(rotatable[i][j]=='F') rotatable[i][j]='G';

  for (i = 0; i < GME_employees; i++)
	  { fprintf(fp,"%s",employeename[i]);
	  	for ( j = 0; j < totaldays; j++)
	        fprintf(fp,",%c",rotatable[i][j]);
		    fprintf(fp,"\n");
	  }
	  fprintf(fp,"\n");
  for (i = GME_employees; i < (GME_employees+G_employees); i++)
	  { fprintf(fp,"%s",employeename[i]);
	  	for ( j = 0; j < totaldays; j++)
	        fprintf(fp,",%c",rotatable[i][j]);
		    fprintf(fp,"\n");
	  }

fclose(fp);
fclose(fp1);
}