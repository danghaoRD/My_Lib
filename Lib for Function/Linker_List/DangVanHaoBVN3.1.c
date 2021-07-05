/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
long  MASINHVIEN= 160501900;
struct LinkedList_Struc
{
	long	MaSV;
	char 	HoTen[32];
	int 	Tuoi;
	char	Sex;
	float	DiemToan;
	float	DiemVan;
	float	DiemHoa;
	float	DiemLy;
	float	DiemSinh;
	int data;
	struct LinkedList_Struc *next;
};

typedef struct LinkedList_Struc *LinkedList_Type;

LinkedList_Type CreaetNode( int value);
LinkedList_Type AddHead(LinkedList_Type Linked_Head, int value);
LinkedList_Type AddTail(LinkedList_Type Linked_Head, int value);
LinkedList_Type AddAny(LinkedList_Type Linked_Head,int position, int value);
LinkedList_Type DelHead(LinkedList_Type Linked_Head);
LinkedList_Type DelTail(LinkedList_Type Linked_Head);
LinkedList_Type DelAny(LinkedList_Type Linked_Head, int position);
LinkedList_Type GetData(LinkedList_Type Linked_Head, int position);
LinkedList_Type NhapThongTin(void);
void XuatThongTin(LinkedList_Type Linked_Head);
LinkedList_Type SapXepTen(LinkedList_Type LinkedHead);
LinkedList_Type XoaSv(LinkedList_Type linkedHead, long MaSVDEL);

int main()
{
	printf("Helllo\n");
 
    LinkedList_Type test = NhapThongTin();
    test = SapXepTen(test);
    XuatThongTin(test);
    int done=0;
    while(done == 0)
    {
    	int check=0;
    	long dell=0;
    	printf("\n--------------Chon TAC VU----------------\n" );
    	printf("1: Xoa sv theo MSV:\n" );
    	printf("2: them SV:\n" );
    	printf("3: in ra thogn tin:\n" );
    	printf("4: sep lai danh sach\n");
    	printf("5: dung chuong trinh:\n" );
    	scanf("%d", &check );
    	switch (check)
    	{
    		case 1:
			    dell=0;
				printf("\n nhap ma sv muon xoa:" );
				scanf("%ld", &dell);
				test = XoaSv(test, dell);
				break;
			case 2:
				printf("\n them sv" );
				test = AddTail(test, 1);
				break;
			case 3:
				XuatThongTin(test);
				break;
			case 4 :
				test = SapXepTen(test);
				break;
			case 5 :	
				done=1;
				break;
			default:
				break;
		}
    }

	
	XuatThongTin(test);
	
	printf("\n them sv" );
	test = AddTail(test, 1);
	


	return 0;
}

LinkedList_Type XoaSv(LinkedList_Type linkedHead, long MaSVDEL)
{
	LinkedList_Type linkedList_Buff = linkedHead;
	LinkedList_Type linkedList_Buff_loop = linkedHead;
	int pos=0;
	while(linkedList_Buff_loop != NULL)
     {
		LinkedList_Type linkedList_Buff2 = GetData(linkedList_Buff, pos);
		
		if(linkedList_Buff2->MaSV == MaSVDEL)
		{
			linkedList_Buff = DelAny(linkedList_Buff, pos);
			printf("Da xoa tai vi tri %d", pos);
			return linkedList_Buff;
		}
		pos++; 
		linkedList_Buff_loop = linkedList_Buff_loop->next;
     }
     printf("khong co ma sv nay\n");
     return linkedList_Buff;
}

LinkedList_Type SapXepTen(LinkedList_Type LinkedHead)
{
	LinkedList_Type linked_Buff = LinkedHead;
	int num_element =0;
	while(linked_Buff != NULL)
     {
		num_element++;
        linked_Buff = linked_Buff->next;
     }
	int i=0, j=0;
	for(i=0; i<(num_element -1); i++)
	{
		LinkedList_Type linked_Buff_i = GetData(LinkedHead, i);
		for(j=(i+1); j<num_element; j++)
		{
			LinkedList_Type linked_Buff_j = GetData(LinkedHead, j);	
			
			if( strcmp(linked_Buff_i->HoTen, linked_Buff_j->HoTen ) >= 0 )
			{
				long	MaSVbuff 	= linked_Buff_j->MaSV;
				char 	HoTenbuff[34] ; 
				int 	Tuoibuff	= linked_Buff_j->Tuoi;
				char	Sexbuff		= linked_Buff_j->Sex;
				float	DiemToanbuff= linked_Buff_j->DiemToan;
				float	DiemVanbuff = linked_Buff_j->DiemVan;
				float	DiemHoabuff = linked_Buff_j->DiemHoa;
				float	DiemLybuff  = linked_Buff_j->DiemLy;
				float	DiemSinhbuff= linked_Buff_j->DiemSinh;
				
				int k=0;
				for( k =0 ; k<=strlen(linked_Buff_j->HoTen); k++)
				{
		 			HoTenbuff[k] = linked_Buff_j->HoTen[k];
				}
				
//				LinkedList_Type linked_Buff_new;
//				linked_Buff_new->next = linked_Buff_j->next;
				
				
			 	for( k =0 ; k<=strlen(linked_Buff_i->HoTen ); k++)
				{
					//	printf("%c\n",HoTen1[0]);
					linked_Buff_j->HoTen[k] = linked_Buff_i->HoTen[k];
				}
				linked_Buff_j->MaSV 	= linked_Buff_i->MaSV;
				linked_Buff_j->Tuoi 	= linked_Buff_i->Tuoi;
				
				linked_Buff_j->Sex 	 	= linked_Buff_i->Sex;
				linked_Buff_j->DiemToan = linked_Buff_i->DiemToan;
				linked_Buff_j->DiemVan  = linked_Buff_i->DiemVan;
				linked_Buff_j->DiemHoa  = linked_Buff_i->DiemHoa;
				linked_Buff_j->DiemLy   = linked_Buff_i->DiemLy;
				linked_Buff_j->DiemSinh = linked_Buff_i->DiemSinh; 
		 		
				for( k =0 ; k<=strlen(HoTenbuff); k++)
				{
				//	printf("%c\n",HoTen1[0]);
				linked_Buff_i->HoTen[k] = HoTenbuff[k];
				}
				linked_Buff_i->MaSV 	= MaSVbuff;
				linked_Buff_i->Tuoi 	= Tuoibuff;
				
				linked_Buff_i->Sex  	= Sexbuff;
				linked_Buff_i->DiemToan = DiemToanbuff;
				linked_Buff_i->DiemVan  = DiemVanbuff;
				linked_Buff_i->DiemHoa  = DiemHoabuff;
				linked_Buff_i->DiemLy   = DiemLybuff;
				linked_Buff_i->DiemSinh = DiemSinhbuff;
				 
				
			}
			
			
			
			
		}
	}
	return LinkedHead;
	
}
 void XuatThongTin(LinkedList_Type Linked_Head)
 {
 	printf("\n------------------Thong tin da co la----------------------\n" ); 
     LinkedList_Type linkedList_Buff = Linked_Head;
     while(linkedList_Buff != NULL)
     {
        printf("Ho ten : %s\t",linkedList_Buff->HoTen); 
    	
    	printf("MSV: %ld\t", linkedList_Buff->MaSV);
    	
    	printf("tuoi: %d\t", linkedList_Buff->Tuoi);
    	
    	printf("Gioi tinh: %d\t", linkedList_Buff->Sex);
    	printf("diem toan: %0.2f\t", linkedList_Buff->DiemToan);
    	printf("diem van: %0.2f\t", linkedList_Buff->DiemVan);
    	printf("diem hoa: %0.2f\t", linkedList_Buff->DiemHoa);
    	printf("diem ly: %0.2f\t", linkedList_Buff->DiemLy);
    	printf("diem sinh: %0.2f\n", linkedList_Buff->DiemSinh);

        linkedList_Buff = linkedList_Buff->next;
     }
 }
 
 LinkedList_Type NhapThongTin(void)
 {
     int sl=0;
     printf("So Sinh vien: ");
     scanf("%d", &sl);
     if( sl == 0)
     {
         printf("Reset va Nhap nhieu hon di:\n");
         
        // return NUll;
     }
     else
     {
         printf("sinh vien 1: \n");
         LinkedList_Type linkedList_Buff = CreaetNode(0);
        int i;
         for(i=1; i < sl; i++)
         {
             printf("sinh vien %d: \n", (i+1));
             linkedList_Buff = AddTail(linkedList_Buff, i);
         }
         return linkedList_Buff;
     }
 }


LinkedList_Type CreaetNode(int value)
{
 

	LinkedList_Type linkedList_Buff;
	linkedList_Buff = (LinkedList_Type) malloc(sizeof(struct LinkedList_Struc));

	linkedList_Buff->next =  NULL;
    
    long	MaSV1;
	char 	HoTen1[34] ; 
	int 	Tuoi1;
	char	Sex1;
	float	DiemToan1;
	float	DiemVan1;
	float	DiemHoa1;
	float	DiemLy1;
	float	DiemSinh1;
	
	printf("Nhap Ten(Nhap ten thoi nhe ^^): ");  
// 	gets(HoTen1); 
// 	fflush(stdin);
    scanf("%s", HoTen1);

	printf("Gioi tinh (1-Nam  0-Nu):");
	scanf("%d", &Sex1);
	
	printf("Tuoi: ");
	scanf("%d", &Tuoi1);

	
	printf("Diem Toan:");
	scanf("%f", &DiemToan1);
	
	printf("Diem Van:");
	scanf("%f", &DiemVan1);
	
	printf("Diem Hoa:");
	scanf("%f", &DiemHoa1);
	
	printf("Diem Ly:");
	scanf("%f", &DiemLy1);
	
	printf("Diem Sinh:");
	scanf("%f", &DiemSinh1);
	
	
	
	
	
	int j=0;
	for( j =0 ; j<=strlen(HoTen1); j++)
	{
	//	printf("%c\n",HoTen1[0]);
		linkedList_Buff->HoTen[j] = HoTen1[j];
	}
	MASINHVIEN++;
	linkedList_Buff->MaSV = MASINHVIEN;
	linkedList_Buff->Tuoi = Tuoi1;
  	
  	linkedList_Buff->Sex  = Sex1;
	linkedList_Buff->DiemToan = DiemToan1;
	linkedList_Buff->DiemVan  = DiemVan1;
	linkedList_Buff->DiemHoa  = DiemHoa1;
	linkedList_Buff->DiemLy   = DiemLy1;
	linkedList_Buff->DiemSinh = DiemSinh1;
	
	printf("%s\t",linkedList_Buff->HoTen); 
	
	printf("MSV: %ld\t", linkedList_Buff->MaSV);
	
	printf("tuoi: %d\t", linkedList_Buff->Tuoi);
	
	printf("Gioi tinh: %d\t", linkedList_Buff->Sex);
	printf("diem toan: %0.2f\t", linkedList_Buff->DiemToan);
	printf("diem van: %0.2f\t", linkedList_Buff->DiemVan);
	printf("diem hoa: %0.2f\t", linkedList_Buff->DiemHoa);
	printf("diem ly: %0.2f\t", linkedList_Buff->DiemLy);
	printf("diem sinh: %0.2f\n", linkedList_Buff->DiemSinh);

	linkedList_Buff->data = value;

	return linkedList_Buff;
}

LinkedList_Type AddHead(LinkedList_Type Linked_Head, int value)
{
	LinkedList_Type linkedList_Buff = CreaetNode(value);
	if (Linked_Head == NULL)
	{
		Linked_Head = linkedList_Buff;
	}
	else
	{
		linkedList_Buff->next = Linked_Head;
		Linked_Head = linkedList_Buff;
	}

	return Linked_Head;
}

LinkedList_Type AddTail(LinkedList_Type Linked_Head, int value)
{
	LinkedList_Type linkedList_BuffNew, linkedList_BuffAdd;
	linkedList_BuffNew = CreaetNode(value);
	if(Linked_Head == NULL)
	{
		Linked_Head = linkedList_BuffNew;
	}
	else
	{
		linkedList_BuffAdd = Linked_Head;
		while(linkedList_BuffAdd->next != NULL)
		{
			linkedList_BuffAdd = linkedList_BuffAdd->next;
		}
		linkedList_BuffAdd->next = linkedList_BuffNew;
	}
	return Linked_Head;
}

LinkedList_Type AddAny(LinkedList_Type Linked_Head,int position, int value)
{
if(position ==0 || Linked_Head == NULL)
	{
		Linked_Head = CreaetNode(value);
	}
	else
	{
		int Pos_Buff =1;
		LinkedList_Type linkedList_Buff = Linked_Head;

		while((linkedList_Buff != NULL) && (Pos_Buff != position))
		{
			//printf("  %d element\n",Pos_Buff);
			linkedList_Buff = linkedList_Buff->next;
			Pos_Buff++;
		}

		if(Pos_Buff != position)
		{
			Linked_Head = AddHead(Linked_Head, value);
			printf("Linked just has %d element\n",Pos_Buff);
		}
		else
		{
			LinkedList_Type linkedList_Buff2 = CreaetNode(value);  
			linkedList_Buff2->next = linkedList_Buff->next;
			linkedList_Buff->next = linkedList_Buff2;
		 

			
		}
	}

	return Linked_Head;
}

LinkedList_Type DelHead(LinkedList_Type Linked_Head)
{
	if(Linked_Head != NULL)
	{
		Linked_Head = Linked_Head->next;
	}
	return Linked_Head;
}
LinkedList_Type DelTail(LinkedList_Type Linked_Head)
{
	if(Linked_Head == NULL || Linked_Head->next == NULL)
	{
		return DelHead(Linked_Head);
	}

	LinkedList_Type linkedList_Buff = Linked_Head;

	while(linkedList_Buff->next->next != NULL)
	{
		linkedList_Buff = linkedList_Buff-> next;

	}

	linkedList_Buff->next = NULL;

	return Linked_Head;
}

LinkedList_Type DelAny(LinkedList_Type Linked_Head, int position)
{
	if(Linked_Head == NULL || position == 0 || Linked_Head->next == NULL)
	{
		Linked_Head = DelHead(Linked_Head);
	}

	else
	{
		int Pos_Buff = 1;
		LinkedList_Type linkedList_Buff = Linked_Head;
		while(linkedList_Buff->next->next != NULL &&  Pos_Buff != position)
		{
			linkedList_Buff = linkedList_Buff->next;
			Pos_Buff ++;
		}
		if(Pos_Buff != position)
		{
			Linked_Head = DelHead(Linked_Head);
		}
		else
		{
			linkedList_Buff->next = linkedList_Buff->next->next;
		}
	}

	return Linked_Head;
}

LinkedList_Type GetData(LinkedList_Type Linked_Head, int position)
{
	int Pos_Buff =0;
	LinkedList_Type linkedList_Buff = Linked_Head;
	while(linkedList_Buff-> next != NULL && Pos_Buff != position)
	{
		Pos_Buff++;
		linkedList_Buff = linkedList_Buff->next;
	}

	return linkedList_Buff;
}

