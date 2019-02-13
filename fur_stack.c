// progamme to simulate working pattern of furniture shop
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct furniture
{
	char fur_name[100];
	int model_no;
	float price;
};

struct customerdetails

{
	char customername[20];
	char address[100];
	char ph[10];
};

struct stack
{
struct furniture s[20];
int top;
};

int isempty(struct stack);
void push(struct stack *,struct furniture ptr);
struct furniture pop(struct stack *);
void readcustdtls(struct customerdetails *);
void displaycustdtls(struct customerdetails);
void final_bill();
void display(struct stack);
int cnt=0;
struct furniture ptr;
struct stack stk;
struct furniture bill;
char filename[20];
FILE *fc;

int main()
{
	FILE *fp;
	FILE *ft;
	FILE *fc;
    stk.top=-1;
	int ch,choice,n,i,flag=0;
	char tmp[100];
	printf("WELCOME TO INNOCENT TRADERS\n");
	printf("Enter file name\n");
	scanf("%s",filename);
	for(;;)
	{
	printf("\n1.Add new furniture\n2.Display\n3.Search\n4.delete items\n5.bill\n6.exit\n");
	scanf("%d",&choice);
	if(choice==6)
		break;
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
			  fprintf(fp,"furniture name: %s\tmodel number: %d\tprice: %f\n",ptr.fur_name,ptr.model_no,ptr.price);
			}
			fclose(fp);
			break;
		case 2:
			// to display data
		    fp=fopen(filename,"r");
			printf("furniture name\t| model no\t|  price\n");
			//fprintf(fp,"furniture name\t|  model no\t|  price\n");			
			while(!feof(fp))
			{
			
			fscanf(fp,"furniture name:\t%s\nmodel number:\t%d\nprice:\t%f\n",ptr.fur_name,&ptr.model_no,&ptr.price);
			printf("%s\t\t %d\t\t %f\n",ptr.fur_name,ptr.model_no,ptr.price);	         
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
        	//fscanf(fp,"%s%d%f",ptr->fur_name,&ptr->model_no,&ptr->price);
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
				push(&stk,ptr);
				fclose(fc);
				printf("\n\nBuyed items are:\n");
				display(stk);
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
				//fscanf(fp,"%s%d%f",ptr->fur_name,&ptr->model_no,&ptr->price); 
				//if(feof(fp))
				 // break;		    	
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
		   printf("\nNumber of records deleted: %d",flag);
		   break;
		
	case 5: final_bill();
	        exit(0);
	        break;
	case 6: break; 
	default:printf("invalid choice\n");      	
   }
   }	
 
 return(0);
 }

//to read customer details
void readcustdtls(struct customerdetails *r)
{
	fc=fopen("customer_details.txt","a");
	printf("Enter customer details(name,address,phno.)\n");
	scanf("%s%s%s",r->customername,r->address,r->ph);
	fprintf(fc,"customer name: %s\naddress: %s\nphone number: %s\n",r->customername,r->address,r->ph);
}

//to display customer details
void displaycustdtls(struct customerdetails x)
{
    printf("Customer Name: %s\nAddress      : %s\nPh No.       : %s\n",x.customername,x.address,x.ph);
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
	while(!isempty(stk))
	{
	bill=pop(&stk);
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
	printf("\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	fprintf(fc,"\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n");
    fclose(fc);
}

//push pop function

int isempty(struct stack s)
{
if(s.top==-1)
return(1);
else
return(0);
}

void display(struct stack stk)
{
	int i;
	printf("\nfurniture Name\tModel Number\tPrice\n");
	for(i=0;i<=stk.top;i++)
	{
		printf("%s\t\t %d\t\t %f\n",stk.s[i].fur_name,stk.s[i].model_no,stk.s[i].price);
	}
}
void push(struct stack *ptrs,struct furniture ptr)
{
ptrs->s[++(ptrs->top)]=ptr;
}

struct furniture pop(struct stack *ptrs)
{
return(ptrs->s[(ptrs->top)--]);
}

