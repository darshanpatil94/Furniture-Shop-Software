//progamme to simulate working pattern of furniture shop
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define qsize 10

struct furniture
{
	char fur_name[40];
	int model_no;
	float price;
	float grand_total;	
};

struct customerdetails
{
	char customername[20];
	char address[100];
	char ph[10];
	char date[12];
	struct furniture bill;
};

struct queue
{
struct furniture Q[qsize];
int front,rear;
};

int full(struct queue);
int empty(struct queue);
void insert(struct queue *,struct furniture);
struct furniture Delete(struct queue *);
void display(struct queue);
void readcustdtls(struct customerdetails *);
void displaycustdtls(struct customerdetails);
void final_bill();
void mergeSort(int low,int mid,int high);
void partition(int low,int high);

FILE *fc;
int cnt=0;
struct furniture ptr;
struct furniture data;
struct queue q;
struct customerdetails cd;

char filename[20];

int main()
{
	FILE *fp;
	FILE *ft;
	FILE *fc;
    q.rear=-1;
    q.front=0;
	int ch,ch1,i,choice,n,fg=0,flag=0,m2,m1,d1,d2,d3,d4;
	float total=0;
	char tmp[100];
	char date1[12],date2[12];
	printf("WELCOME TO INNOCENT TRADERS\n");
	printf("Enter file name\n");
	scanf("%s",filename);
	do
	{
	printf("\n1.Add new furniture\n2.Display furniture\n3.Search furniture\n4.delete furniture\n5.bill\n6.Query\n7.exit\n");
	scanf("%d",&choice);
	
	switch(choice)
	{
		//to add and append data
		case 1:
			fp=fopen(filename,"a");
			printf("Enter number of funrniture's to be added: ");
			scanf("%d",&n);
			for(i=0;i<n;i++)
			{
			  printf("Enter furniture name:\n ");
			  scanf("%s",ptr.fur_name);
			  printf("Enter model no:\n");
			  scanf("%d",&ptr.model_no);
			  printf("Enter price:\n ");
			  scanf("%f",&ptr.price);
			  fprintf(fp,"furniture name: %s\t  model number: %d\t  price: %f\n",ptr.fur_name,ptr.model_no,ptr.price);
			}
			fclose(fp);
			break;
		case 2:
			// to display data
		    fp=fopen(filename,"r");
			printf("Furniture name\t\t|\tmodel no\t|\tprice\n");		
			while(!feof(fp))
			{
			
			fscanf(fp,"furniture name:\t%s\nmodel number:\t%d\nprice:\t%f\n",ptr.fur_name,&ptr.model_no,&ptr.price);
			printf("%s\t\t\t\t%d\t\t\t%f\n",ptr.fur_name,ptr.model_no,ptr.price);	         
		    }	     
			fclose(fp);
            break;
        case 3:
        	// to search data
        	do
        	{
        	printf("Enter furniture name to be searched: ");
        	scanf("%s",tmp);
        	fp=fopen(filename,"r");
        	while(!feof(fp))
        	{
        	fscanf(fp,"furniture name:\t%s\nmodel number:\t%d\nprice:\t%f\n\n",ptr.fur_name,&ptr.model_no,&ptr.price);	
        	if(strcmp(ptr.fur_name,tmp)==0)
           {
           flag=1;
           printf("Record found\n");
		   printf("furniture name:  %s\tmodel number:  %d\tprice:  %f\n\n",ptr.fur_name,ptr.model_no,ptr.price);
		   printf("would u like to buy it??\n 1->yes\n 2->no\n\n");
				scanf("%d",&ch);
				if(ch==1)
				{
				fc=fopen("customer_details1.txt","a");
				insert(&q,ptr);
				fclose(fc);
				printf("\n\nBuyed items are:\n");
				display(q);
				cnt++;
				break;
				}
				else
				break;           
		   break;
           }
           else
           flag=0;
           }
           if(flag==0)
           {
           	printf("record not found\n");
           }
           printf("\nWould You Like to continue search?\n1->Yes\n2->No\n");
           scanf("%d",&ch1);
           
          }while(ch1==1);
           fclose(fp);
           break;
          
    case 4: //to delete data
	        printf("\nEnter furniture name to be deleted: ");
	        scanf("%s",tmp);
			fp=fopen(filename,"r");
			ft=fopen("temp.txt","w");
			while(!feof(fp))
			{
			    fscanf(fp,"furniture name:\t%s\nmodel number:\t%d\nprice:\t%f\n",ptr.fur_name,&ptr.model_no,&ptr.price);
				//fscanf(fp,"%s%d%f",ptr->fur_name,&ptr->model_no,&ptr->price); 
				if(feof(fp))
				  break;
		    	
				if(strcmp(ptr.fur_name,tmp)!=0)
		    	{
		    		fprintf(ft,"furniture name:\t%s\nmodel number:\t%d\nprice:\t%f\n",ptr.fur_name,ptr.model_no,ptr.price);
		    	}
		    	else
		    	  flag++;
		   }
		   fclose(fp);
		   fclose(ft);
		   remove(filename);
		   rename("temp.txt",filename);
		   printf("\nNumber of records deleted: %d\n\n",flag);
		   break;
		
	case 5: final_bill();
	        //exit(0);
	        break;
	case 6: 
	system("cls");
    fc=fopen("customer_details1.txt","r");
    printf("\nEnter 2 dates between which you need to find records in the format DD/MM/YYYY\n");
    scanf("%s%s",date1,date2);
    
    printf("\n\n--------------------------------------------------------------------------------\n");
    printf("\tCustomer_Name\t\t|\tDate\t\t|\tAmount\n");
    printf("--------------------------------------------------------------------------------\n");
    while(!feof(fc))
    {
       //m1=m2=d1=d2=d3=d4=0;
       //fscanf(fc,"%s\n%s\n%s\n%s\n%s\n%d\n%f\n%f",cd.customername,cd.address,cd.ph,cd.date,cd.bill.fur_name,&cd.bill.model_no,&cd.bill.price,&cd.bill.grand_total);
       fscanf(fc,"customer name: %s\naddress: %s\nphone number: %s\nDate: %s\ngrand_total: %f\n",cd.customername,cd.address,cd.ph,cd.date,&cd.bill.grand_total);
	   //printf("\n%s\n\n",cd.date);	   	  
	   m2=(cd.date[3]-'0')*10+(cd.date[4]-'0');
       m1=(cd.date[0]-'0')*10+(cd.date[1]-'0');
       d1=(date1[0]-'0')*10+(date1[1]-'0');
       d2=(date1[3]-'0')*10+(date1[4]-'0');
       d3=(date2[0]-'0')*10+(date2[1]-'0');
       d4=(date2[3]-'0')*10+(date2[4]-'0');
       //printf("%d\n%d\n%d\n%d\n%d\n%d\n",m1,m2,d1,d2,d3,d4);
    
	   if(m2>=d2&&m2<=d4)
       {
            if((m1>=d1&&m1<=d3)||(m2>=d2&&m2<=d4))
            {
            if(m2!=d4)
            {
             printf("\t%s\t\t\t\t%s\t\tRs.%f\n",cd.customername,cd.date,cd.bill.grand_total);
             total=total+cd.bill.grand_total;
			 fg=1;
            }//printf("%s\t\t%s\t\t%f\n\n",cd.customername,cd.date,cd.bill.grand_total);
			if(m1<=d3&&m2==d4)
			{
			 printf("\t%s\t\t\t\t%s\t\tRs.%f\n",cd.customername,cd.date,cd.bill.grand_total);
			 total=total+cd.bill.grand_total;
			 fg=1;
			}
			} 
       }
    }
    if(fg==0)
    {
    	printf("\nNo Records Found b/w dates %s and %s\n\n",date1,date2);
    }
    else
    {
    printf("--------------------------------------------------------------------------------\n");
    printf("Total Sales b/w %s and %s\t\t=\tRs.%f\n",date1,date2,total);   
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	fclose(fc);
    break;
		
	case 7: break; 
	
	default:printf("\nInvalid Choice\n");      	
   }
   }while(choice!=7);		
 return(0);
 }

//to read customer details
void readcustdtls(struct customerdetails *r)
{
	fc=fopen("customer_details1.txt","a");
	printf("\nEnter customer details(name,address,phno.,date of purchase):\n");
	scanf("%s%s%s%s",r->customername,r->address,r->ph,r->date);
	//fprintf(fc,"\t\t\tINNOCENT FURNITURE SHOP\n");
	//fprintf(fc,"-------------------------------------------------------------------------------\n");
	//fprintf(fc,"customer name: %s\naddress: %s\nphone number: %s\nDate: %s\n",r->customername,r->address,r->ph,r->date);
}

//to display customer details
void displaycustdtls(struct customerdetails x)
{
    printf("Customer Name: %s\nAddress      : %s\nPh No.       : %s\nDate:  %s\n",x.customername,x.address,x.ph,x.date);
}


//to calculate bill
void final_bill()
{
	//FILE *ft;
	//int p,flag=0;
	float total=0,vat,discount;
	//struct customerdetails cd;
	readcustdtls(&cd);

	partition(q.front,q.rear);
	
	system("cls");
	printf("\t\t\tINNOCENT FURNITURE SHOP\n");
	printf("-------------------------------------------------------------------------------\n");
	displaycustdtls(cd);
	printf("\n-------------------------------------------------------------------------------");
	//fprintf(fc,"\n-------------------------------------------------------------------------------");	
	printf("\nFurniture name\t\t|\tModel no\t|\tPrice\n");
	printf("--------------------------------------------------------------------------------\n");
	//fprintf(fc,"\nFurniture name\t\t|\tModel no\t|\tPrice\n");
	//fprintf(fc,"--------------------------------------------------------------------------------\n");
		
	while(!empty(q))
	{
	cd.bill=Delete(&q);
    printf("%s\t\t\t\t%d\t\t\tRs.%f\n",cd.bill.fur_name,cd.bill.model_no,cd.bill.price); 
	//fprintf(fc,"%s\t\t\t\t%d\t\t\tRs.%f\n",cd.bill.fur_name,cd.bill.model_no,cd.bill.price);       
	total=total + cd.bill.price;
    }
    printf("-------------------------------------------------------------------------------");
   //fprintf(fc,"-------------------------------------------------------------------------------");
	printf("\nTotal amount:\t\t\t\t\t\tRs.%f",total);
  //fprintf(fc,"\nTotal amount:\t\t\t\t\t\tRs.%f",total);
	vat=(0.05)*total;
	discount=0.15*total;
	printf("\nVat:\t\t\t\t\t\t\tRs.%f\n",vat);
	printf("Discount:\t\t\t\t\t\tRs.%f",discount);
	//fprintf(fc,"\nVat:\t\t\t\t\t\t\tRs.%f\n",vat);
	//fprintf(fc,"Discount:\t\t\t\t\t\tRs.%f",discount);
	cd.bill.grand_total=total+vat-discount;
	printf("\n-------------------------------------------------------------------------------");
	//fprintf(fc,"\n-------------------------------------------------------------------------------");
	printf("\nGrand total:\t\t\t\t\t\tRs.%f\n\n",cd.bill.grand_total);
	//fprintf(fc,"\nGrand total:\t\t\t\t\t\tRs.%f\n\n",cd.bill.grand_total);
	printf("\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	//fprintf(fc,"\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n");
    fprintf(fc,"customer name: %s\naddress: %s\nphone number: %s\nDate: %s\ngrand_total: %f\n",cd.customername,cd.address,cd.ph,cd.date,cd.bill.grand_total);
	fclose(fc);
}



void partition(int low,int high)
{
    int mid;
    if(low<high)
	{
         mid=(low+high)/2;
         partition(low,mid);
         partition(mid+1,high);
         mergeSort(low,mid,high);
    }
}

void mergeSort(int low,int mid,int high)
{

    int i,m,k,l;
	struct furniture temp[qsize];

    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high))
	{

         if(q.Q[l].price<=q.Q[m].price)
		 {
             temp[i]=q.Q[l];
             l++;
         }
         else
		 {
             temp[i]=q.Q[m];
             m++;
         }
         i++;
    }

    if(l>mid)
	{
         for(k=m;k<=high;k++)
		 {
             temp[i]=q.Q[k];
             i++;
         }
    }
    else
	{
         for(k=l;k<=mid;k++)
		 {
             temp[i]=q.Q[k];
             i++;
         }
    }
   
    for(k=low;k<=high;k++)
	{
         q.Q[k]=temp[k];
    }
}


int full(struct queue q)
{
if(q.rear==(qsize-1))
return(1);
else
return(0);
}
int empty(struct queue q)
{
if(q.front>q.rear)
return(1);
else
return(0);
}

void display(struct queue q)
{
int i;
printf("\nfurniture Name\tModel Number\tPrice\n");
for(i=q.front;i<=q.rear;i++)
printf("%s\t\t %d\t\t %f\n",q.Q[i].fur_name,q.Q[i].model_no,q.Q[i].price);
}

void insert(struct queue *ptrq,struct furniture ptr)
{
ptrq->Q[++(ptrq->rear)]=ptr;
}

struct furniture Delete(struct queue *ptrq)
{
int i;
data=ptrq->Q[ptrq->front];
for(i=1;i<=ptrq->rear;i++)
ptrq->Q[i-1]=ptrq->Q[i];
(ptrq->rear)--;
return(data);
}

