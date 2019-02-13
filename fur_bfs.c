// progamme to simulate working pattern of furniture shop
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
#define qsize 10

struct furniture
{
	char fur_name[40];
	int model_no;
	float price;
};

struct customerdetails
{
	char customername[20];
	char address[100];
	char ph[10];
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
int bfs(struct furniture);
void displaybfs();

FILE *fc;
int cnt=0;
struct furniture ptr;
struct furniture data;
struct queue q,q1;
struct furniture bill;
char filename[20];
char que[20],b[20],v;
int i,j,p=0;
struct furniture arr[20];
char ajMat[20][20];


int main()
{
	FILE *fp;
	FILE *ft;
	FILE *fc;
    q.rear=-1;
    q.front=0;
    
	int ch,i,choice,n,flag=0;
	char tmp[100];
	printf("WELCOME TO INNOCENT TRADERS\n");
	printf("Enter file name\n");
	scanf("%s",filename);
	do
	{
	printf("\n1.Add new furniture\n2.Display\n3.Search\n4.delete items\n5.bfs\n6.bill\n7.Exit\n");
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
			printf("furniture name\t\t|\tmodel no\t|\tprice\n");			
			while(!feof(fp))
			{
			
			fscanf(fp,"furniture name:\t%s\nmodel number:\t%d\nprice:\t%f\n",ptr.fur_name,&ptr.model_no,&ptr.price);
			printf("%s\t\t\t\t%d\t\t\t%f\n",ptr.fur_name,ptr.model_no,ptr.price);	         
		    }	     
			fclose(fp);
            break;
        case 3:
        	// to search data
        	printf("enter furniture name to be searched\n");
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
				fc=fopen("customer_details.txt","a");
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
		   
	case 5: 
	system("cls");
	printf("\nEnter the value in adjancency matrix in from of 'y' or 'n'\n");
    printf("If there exists an edge between two vertices than 'y' otherwise 'n'\n\n");
    for(i=q.front;i<=q.rear;i++)
    printf("\t%s\t",q.Q[i].fur_name);
	    
    for(i=q.front;i<=q.rear;i++)
    {
        printf("\n%s",q.Q[i].fur_name);
        for(j=q.front;j<=q.rear;j++)
        {
            printf("\t%c\t",v=getchar());
             ajMat[i][j]=v;
        }
        printf("\n\n");
    }
    
	for(i=q.front;i<=q.rear;i++)
    {
    bfs(q.Q[i]);
    }
    displaybfs();
    //getchar();
    printf("\n\n\n");
    break;		
		
	case 6: final_bill();
	        //exit(0);
	        break;
	case 7: break; 
	default:printf("invalid choice\n");      	
   }
   }while(choice!=7);		
 return(0);
}

void displaybfs()
{
     printf("BFS of Graph: ");
     for(i=0; i<=p; i++)
     printf("%s  ",arr[i].fur_name);
}

char unVisit(struct furniture val)
{
    for(i=q1.front;i<=q1.rear;i++)
    {
         if(val.fur_name==q1.Q[i].fur_name)
         return 0;
    }
return 1;
}

int bfs(struct furniture f)
{
     struct furniture m;
     int i=0,j=0;
     q1.rear=-1;
     q1.front=0;
     if(q1.rear<q1.front)
     {
         insert(&q1,f);
     }
     else
	 {
	  for(j=q1.front;j<=q1.rear;j++) 
     {
         if(ajMat[i][j]=='y')
         {
              if(unVisit(f))
              {
                   insert(&q1,f);
              }
         }
     }
    }
     m=Delete(&q1);
     arr[p]=m;
     p++;
     return 0;
}


//to read customer details
void readcustdtls(struct customerdetails *r)
{
	fc=fopen("customer_details.txt","a");
	printf("\nEnter customer details(name,address,phno.):\n");
	scanf("%s%s%s",r->customername,r->address,r->ph);
	fprintf(fc,"\t\t\tINNOCENT FURNITURE SHOP\n");
	fprintf(fc,"-------------------------------------------------------------------------------\n");
	fprintf(fc,"customer name: %s\naddress: %s\nphone number: %s\n\n",r->customername,r->address,r->ph);
}

//to display customer details
void displaycustdtls(struct customerdetails x)
{
    printf("Customer Name: %s\nAddress      : %s\nPh No.       : %s\n\n",x.customername,x.address,x.ph);
}


// to calculate bill
void final_bill()
{
	//FILE *ft;
	//int p,flag=0;
	float total=0,vat,discount,grand_total;
	struct customerdetails cd;	
	readcustdtls(&cd);
	system("cls");
	printf("\t\t\tINNOCENT FURNITURE SHOP\n");
	printf("-------------------------------------------------------------------------------\n");
	displaycustdtls(cd);
	printf("\n-------------------------------------------------------------------------------");
	fprintf(fc,"\n-------------------------------------------------------------------------------");	
	printf("\nFurniture name\t\t|\tModel no\t|\tPrice\n");
	printf("--------------------------------------------------------------------------------\n");
	fprintf(fc,"\nFurniture name\t\t|\tModel no\t|\tPrice\n");
	fprintf(fc,"--------------------------------------------------------------------------------\n");
	while(!empty(q))
	{
	bill=Delete(&q);
    printf("%s\t\t\t\t%d\t\t\tRs.%f\n",bill.fur_name,bill.model_no,bill.price); 
	fprintf(fc,"%s\t\t\t\t%d\t\t\tRs.%f\n",bill.fur_name,bill.model_no,bill.price);       
	total=total + bill.price;
    }
    
    printf("-------------------------------------------------------------------------------");
    fprintf(fc,"-------------------------------------------------------------------------------");
	printf("\nTotal amount:\t\t\t\t\t\tRs.%f",total);
	fprintf(fc,"\nTotal amount:\t\t\t\t\t\tRs.%f",total);
	vat=(0.05)*total;
	discount=0.15*total;
	printf("\nVat:\t\t\t\t\t\t\tRs.%f\n",vat);
	printf("Discount:\t\t\t\t\t\tRs.%f",discount);
	fprintf(fc,"\nVat:\t\t\t\t\t\t\tRs.%f\n",vat);
	fprintf(fc,"Discount:\t\t\t\t\t\tRs.%f",discount);
	grand_total=total+vat-discount;
	printf("\n-------------------------------------------------------------------------------");
	fprintf(fc,"\n-------------------------------------------------------------------------------");
	printf("\nGrand total:\t\t\t\t\t\tRs.%f\n\n",grand_total);
	fprintf(fc,"\nGrand total:\t\t\t\t\t\tRs.%f\n\n",grand_total);
	printf("\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	fprintf(fc,"\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n");
    fclose(fc);
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
