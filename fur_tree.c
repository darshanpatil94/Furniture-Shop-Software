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

struct node
{
    struct customerdetails data;
    struct node *lchild,*rchild;
};

void insert(struct node *,struct node *);
void inorder(struct node *);
void preorder(struct node *);
float total(struct node *);
void postorder(struct node *);
void readcustdtls(struct customerdetails *);
void displaycustdtls(struct customerdetails);
void final_bill(struct node *);

FILE *fc;
int cnt=0;
float tl=0;
struct furniture ptr;
struct furniture data;
struct customerdetails cd;
char filename[20];

int main()
{
	FILE *fp;
	FILE *ft;
	FILE *fc;
    
    struct node *new_node,*root,*parent,*get_node();
	int ch,i,choice,n,flag=0,j=0,m2,m1,d1,d2,d3,d4,ans;
	char tmp[100];
	char date1[9],date2[9];
	
	root=NULL;
	printf("WELCOME TO INNOCENT TRADERS\n");
	printf("Enter file name\n");
	scanf("%s",filename);
	for(;;)
	{
	printf("\n1.Add new furniture\n2.Display furniture\n3.Search furniture\n4.Delete furniture\n5.Display buyed items\n6.Bill\n7.Exit\n");
	scanf("%d",&choice);
	if(choice==7)
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
				fc=fopen("customer_details.txt","a");
				new_node=get_node();
				new_node->data.bill=ptr;
				 if(root==NULL)
                   {
 	                 root=new_node;
 	                //printf("%s\t\t\t\t%d\t\t\tRs.%f\n",root->data.bill.fur_name,root->data.bill.model_no,root->data.bill.price);
 	                printf("\nroot node created\n\n");
                   }
				 else
				 {
				insert(root,new_node);
			     }
				fclose(fc);
				printf("\n\nBuyed items are:\n");				
			    inorder(root);
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
           
           printf("\n\nWould you like to continue searching: 1->yes\t2->No\n");
           scanf("%d",&ans);
           }while(ans==1);
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
		   
		    
    case 5:   
         system("cls");
    	do
    	{
    	  printf("\n\nEnter traversal:\n1-> preorder\t2-> inorder\t3-> postoder\t4-> Main menu\n");
    	  scanf("%d",&ch);
    	   switch(ch)
    	   {
    	   	case 1: 
    	   	       printf("\nPreorder traversal of buyed items\n");
    	   	       printf("\n\nFurniture name\t\t|\tModel no\t|\tPrice\n");
			       preorder(root);
    	   	        break;
    	   	case 2: printf("\nInorder traversal of buyed items\n");
    	   	        printf("\n\nFurniture name\t\t|\tModel no\t|\tPrice\n");
			        inorder(root);
    	   	        break;
    	   	case 3: printf("\nPostorder traversal of buyed items\n");
    	   	        printf("\n\nFurniture name\t\t|\tModel no\t|\tPrice\n");
			        postorder(root);
    	   	        break;
    	   	case 4: break;	
          }
    	}while(ch!=4);
        
		 break;
		
	case 6: final_bill(root);
	        break;
    
	case 7: break; 
	default:printf("\nInvalid Choice\n");      	
   }
   }
   return(0);		
 }

//to read customer details
void readcustdtls(struct customerdetails *r)
{
	fc=fopen("customer_details.txt","a");
	printf("\nEnter customer details(name,address,phno.,date of purchase):\n");
	scanf("%s%s%s%s",r->customername,r->address,r->ph,r->date);
	fprintf(fc,"\t\t\tINNOCENT FURNITURE SHOP\n");
	fprintf(fc,"-------------------------------------------------------------------------------\n");
	fprintf(fc,"customer name: %s\naddress: %s\nphone number: %s\nDate: %s\n",r->customername,r->address,r->ph,r->date);
}

//to display customer details
void displaycustdtls(struct customerdetails x)
{
    printf("Customer Name: %s\nAddress      : %s\nPh No.       : %s\nDate         : %s\n",x.customername,x.address,x.ph,x.date);
}


//to calculate bill
void final_bill(struct node *root)
{
	//FILE *ft;
	//int p,flag=0;
	float ttl,vat,discount,grand_total;
	//struct customerdetails cd;
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
    inorder(root);
	 
    ttl=total(root);
    printf("-------------------------------------------------------------------------------");
    fprintf(fc,"-------------------------------------------------------------------------------");
	printf("\nTotal amount:\t\t\t\t\t\tRs.%f",ttl);
	fprintf(fc,"\nTotal amount:\t\t\t\t\t\tRs.%f",ttl);
	vat=(0.05)*ttl;
	discount=0.15*ttl;
	printf("\nVat:\t\t\t\t\t\t\tRs.%f\n",vat);
	printf("Discount:\t\t\t\t\t\tRs.%f",discount);
	fprintf(fc,"\nVat:\t\t\t\t\t\t\tRs.%f\n",vat);
	fprintf(fc,"Discount:\t\t\t\t\t\tRs.%f",discount);
	cd.bill.grand_total=ttl+vat-discount;
	printf("\n-------------------------------------------------------------------------------");
	fprintf(fc,"\n-------------------------------------------------------------------------------");
	printf("\nGrand total:\t\t\t\t\t\tRs.%f\n\n",cd.bill.grand_total);
	fprintf(fc,"\nGrand total:\t\t\t\t\t\tRs.%f\n\n",cd.bill.grand_total);
	printf("\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	fprintf(fc,"\n\nTHANK YOU FOR SHOPPING IN INNOCENT TRADERS\n\n\nVISIT AGAIN\n\n");
    fclose(fc);
}

struct node *get_node()
 {
 struct node *temp;
 temp=(struct node *)malloc(sizeof(struct node));
 temp->lchild=NULL;
 temp->rchild=NULL;
 return(temp);
 }
 
void insert(struct node *root,struct node *new_node)
{
  if(new_node->data.bill.price < root->data.bill.price)
     {
     if(root->lchild==NULL)
       { 
		 root->lchild = new_node;
         //printf("%s\t\t\t\t%d\t\t\tRs.%f\n",root->lchild->data.bill.fur_name,root->lchild->data.bill.model_no,root->lchild->data.bill.price);
         printf("left child created\n\n");
       }
	 else
         insert(root->lchild,new_node);
     }
  if(new_node->data.bill.price > root->data.bill.price)
     {
     if(root->rchild==NULL)
     {
	     root->rchild=new_node;
         printf("right child created\n\n");
     }
     else
         insert(root->rchild,new_node);
     }
}

void inorder(struct node *temp)
{
   if(temp!=NULL)
    {
    inorder(temp->lchild);
    printf("%s\t\t\t\t%d\t\t\tRs.%f\n",temp->data.bill.fur_name,temp->data.bill.model_no,temp->data.bill.price); 
    inorder(temp->rchild);
    }
}

void preorder(struct node *temp)
{
 if(temp!=NULL)
    {
    printf("%s\t\t\t\t%d\t\t\tRs.%f\n",temp->data.bill.fur_name,temp->data.bill.model_no,temp->data.bill.price);
	preorder(temp->lchild);
    preorder(temp->rchild);
    }
}

void postorder(struct node *temp)
{
 if(temp!=NULL)
    {
    postorder(temp->lchild);
    postorder(temp->rchild);
    printf("%s\t\t\t\t%d\t\t\tRs.%f\n",temp->data.bill.fur_name,temp->data.bill.model_no,temp->data.bill.price);
    }
}

float total(struct node *temp)
{
 if(temp!=NULL)
    {
    tl=tl + temp->data.bill.price; 
	total(temp->lchild);
    total(temp->rchild);
    }
    return(tl);
}
