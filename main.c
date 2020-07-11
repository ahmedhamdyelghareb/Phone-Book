#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<string.h>

#define up 72
#define down 80
#define enter 13
#define esc 27
#define home 71
#define end 79

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);


}

struct  NameNode* head  = NULL ;
struct  NameNode* tail  = NULL ;

struct PhoneNode* headPhone  = NULL ;
struct PhoneNode* tailphone  = NULL ;


struct CalledNode* headCall  = NULL ;
struct CalledNode* tailCall  = NULL ;

int identity=0 ;

struct NameNode
{
    int id ;
    char name [20] ;
    int IsDeleted  ;//if 0 person not found .... 1 found
    struct NameNode* next ;
    struct NameNode* prev ;
    struct PhoneNode* firstphone ;
};
struct PhoneNode
{
    int id  ;
    char number [11] ;
    int IsDeleted  ; // if 0 person not found .... 1 found
    struct  PhoneNode* next ;
    struct  PhoneNode* prev ;
};

struct CalledNode
{
    char name[20];
    struct CalledNode* next;
    struct CalledNode* prev;
};

int IncrementIdentity ()
{
    return ++identity ;
}
int GetIdentity ()
{
    return identity ;
}

//////////////////////////////////////////////////////Search function. ////////////////////////////////

struct NameNode *search_by_name(char name [])
{
   struct NameNode* temp=head;
   int i=1;

    while(temp!=NULL)
    {

       i= strcmpi(temp->name,name);
        if(i==0)
            return temp ;
        temp=temp->next;
    }
    return NULL;
} // search by name return full  node
struct PhoneNode *search_by_number(char number [])
{
   struct PhoneNode* temp=headPhone;
   int i=1;

    while(temp!=NULL)
    {

       i= strcmpi(temp->number,number);
        if(i==0)
            return temp ;
        temp=temp->next;
    }
    return NULL;
} // search by number  return full node

struct NameNode *search_by_id_name(int id)
{
    struct NameNode * temp=head;
    while(temp!=NULL)
    {

        if(temp->id==id)
            return temp ;
        temp=temp->next;
    }
    return NULL;
}
struct PhoneNode *search_by_id_phone(int id)
{


    struct PhoneNode * temp=headPhone;
    while(temp!=NULL)
    {

        if(temp->id==id)
            return temp ;
        temp=temp->next;
    }
    return NULL;
}
//////////////////////////////////////////////////////Add Function ////////////////////////////////////
void  appendName(char name [20])
{
     struct NameNode * temp ;
     struct NameNode * checkname;
     temp = (struct NameNode*)malloc(sizeof(struct NameNode )) ;
     temp -> id = IncrementIdentity() ;
     checkname=search_by_name(name);
    if(checkname ==NULL)
    strcpy ( temp -> name , name );
    else{
         do{

         printf("Sorry that name already exists please enter a new one \n ");
          do
                           {
                           printf("Enter the name  of   contact and press Enter: ");
                           _flushall();
                           gets(name);
                           }while(strlen(name)<10||strlen(name)>20);
            checkname=search_by_name(name);
     }
     while(checkname !=NULL);
      strcpy ( temp -> name , name );
}

         if ( head  == NULL)
         {
             head = tail = temp ;
             temp -> next = NULL ;
             temp -> prev = NULL ;
         } // head == null

         else
         {
             temp-> next = NULL ;
             temp -> prev = tail ;
             tail -> next = temp ;
             tail = temp ;
         }


   // printf("append name working fine \n") ;

} // append name
void appendPhone(char number [11] ,int id)
{
    struct PhoneNode * temp ;
    struct PhoneNode * checknum;

     temp = (struct PhoneNode*)malloc(sizeof(struct PhoneNode )) ;

     temp -> id = id;

     checknum=search_by_number(number);
     if(checknum ==NULL)
     strcpy ( temp -> number , number );
        else
        {

            do{

            printf("sorry that number already exists please enter a new one \n");
             do
                           {
                           printf("Enter the phone of contact  and press enter: ");

                            _flushall();
                           gets(number);
                           }
                           while (strlen(number)!=11);
                 checknum=search_by_number(number);
        }while(checknum !=NULL);
         strcpy ( temp -> number , number );
        }
         if ( headPhone  == NULL)
         {
             headPhone = tailphone = temp ;
             temp -> next = NULL ;
             temp -> prev = NULL ;

         } // head == null

         else
         {
             temp-> next = NULL ;
             temp -> prev = tailphone ;
             tailphone -> next = temp ;
             tailphone = temp ;
         }


   //printf("append  phone working fine \n") ;

} // void PhoneAppend


//////////////////////////////////////////////////////Display Function ////////////////////////////////////
void displayAllname( int id )
{
    struct NameNode* temp=head;
    while(temp !=NULL)
    {
        if (temp -> id == id )
        printf(" the name is %s \n ",temp->name);
        temp=temp->next;

    }
  //  printf("display  name is working fine ");
}  // diplay all phone contact
void displayAllPhone(int id)
{

    struct PhoneNode* temp=headPhone;
    while(temp !=NULL)
    {
        if(temp -> id == id)
        printf("the number is %s \n ",temp->number);
        temp=temp->next;

    }
 //   printf("display  phone is working fine ");
}  // diplay all phone contact
void displayAllNameMenu()
{



            char menuContact[count()][20] ;
            int  current=0, back = 0 ;
            char ch ;
            struct NameNode* temp=head;
            struct NameNode *n;


    while(temp !=NULL)
    {
        for (int i = 0 ; i < count(); i++ )
        {

               strcpy(menuContact[i] ,temp -> name );
               temp=temp->next;

        } // for

    } // while

      do
    {
        system("cls");
        printf("Plese Choose Name and press Enter to Call:");
            if(current<0) current = count()-1;
            else if (current > count()-1) current = 0 ;

            for ( int i=0 ; i < count(); i++)
              {

                  if (i==current)
                    textattr(0x70);
                    gotoxy(10,7+2*i);
                    _cprintf("%s",menuContact[i]);
                    textattr(0x07); // to reset default color
              } // for
    ch= getch();
      switch(ch)
    {

         case -32:
         ch = getch();
                         switch(ch)
                         {

                            case 72: // up
                                 current -- ;
                             break ; // up

                             case 80: // down
                                  current ++ ;
                             break;   // down

                             case 71:
                                 current =0 ;
                             break; // home

                             case 79:
                                 current =count() -1  ;
                             break; // end
                         }// ineer switch
         break; // -32


         case 13:
              appendCalled (menuContact[current]);
              back=1;
              system("cls");
              printf("Calling %s...",(menuContact[current]));
              getch();
              menu();
            break;


     } // switch
   }// do
    while (!back) ;
}  // diplay all contact name

//////////////////////////////////////////////////////Delete Function ////////////////////////////////////
void deleteAllphone_by_id(int id)
{

  struct PhoneNode * temp=search_by_id_phone(id);
    do
    {


    if(headPhone==tailphone)
    {
        headPhone=tailphone=NULL;
        free(temp);
    }
    else if(temp==headPhone)
    {
        temp->next->prev=NULL;
        headPhone=temp->next;
        free(temp);
    }
    else if(temp==tailphone)
    {
        tailphone=temp->prev;
        tailphone->next=NULL;
        free(temp);
    }
    else
    {
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        free(temp);
    }

    temp = search_by_id_phone(id);
    } // do
    while ( temp != NULL) ;

}
void deletename_by_id(int id)
{

  struct NameNode * temp=search_by_id_name(id) ;

    if(head==tail)
    {
        head=tail=NULL;
        free(temp);
    }
    else if(temp==head)
    {
        temp->next->prev=NULL;
        head=temp->next;
        free(temp);
    }
    else if(temp==tail)
    {
        tail=temp->prev;
        tail->next=NULL;
        free(temp);
    }
    else
    {
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        free(temp);
    }


}
void deletebyname (char name [])
{
    int getid=0;
     struct NameNode* temp=head;
     struct NameNode* getname= search_by_name(name);
     if(getname==NULL)
     {
       printf("there is no such name in the contact");
     }
      else
      {
        getid=getname->id;
        deletename_by_id(getid);
        deleteAllphone_by_id(getid);
        printf("%s with its all numbers deleted ", name);
    }


} // delete by name

void deletebyphone (char phone[])
{

   struct PhoneNode* temp= search_by_number(phone);
 if(temp==NULL)
 {
     printf("there is no such name in the contact");
 }
 else
 {
   if(headPhone==tailphone)
    {
        headPhone=tailphone=NULL;
        free(temp);
    }
    else if(temp==headPhone)
    {
        temp->next->prev=NULL;
        headPhone=temp->next;
        free(temp);
    }
    else if(temp==tailphone)
    {
        tailphone=temp->prev;
        tailphone->next=NULL;
        free(temp);
    }
    else
    {
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        free(temp);
    }

     printf("%s numbers deleted ", phone);
 }
}

//////////////////////////////////////////////////////Modify Function ////////////////////////////////////
char newName[20];
void modifyName (char oldname[])
{

    struct NameNode* checkname=NULL ;
    struct NameNode* temp=NULL ;

    temp = search_by_name(oldname);
    if(temp==NULL)
    {
        printf("there is no such name in the contact");
    }
    else
    {

       do
       {
         printf("Please enter new name and press Enter : ");
         gets(newName);
       } // do
       while(strlen(newName)<10||strlen(newName)>20);
      checkname=search_by_name(newName);
      if(checkname ==NULL)
       strcpy ( temp -> name , newName );
        else{
         do{

         printf("sorry that name already exists please enter a new one \n ");
          do
                           {
                           printf("Enter the name of contact and press enter: ");
                           _flushall();
                           gets(newName);
                           }while(strlen(newName)<10||strlen(newName)>20);
            checkname=search_by_name(newName);
     }
     while(checkname !=NULL);
     {

     }
     strcpy ( temp -> name , newName );



}
  printf("Done Moifyied name") ;
    }



} // Modify name
void modifyPhone (char phone[])
{

   struct PhoneNode* temp=NULL ;
    struct PhoneNode * checknum;
    int flag = 0 ;
    temp = search_by_number(phone);
    if(temp==NULL)
    {
        printf("there is no such phone in the contact");
    }
    else
    {
       char newPhone[20];
       do
       {
         printf("Please enter new phone and press Enter : ");
         gets(newPhone);
         checknum=search_by_number(newPhone);
         if(checknum ==NULL)
          flag = 1 ;
       } // do
       while( flag==0||strlen(newPhone)!=11);
       strcpy(temp ->number , newPhone);
        printf("Done Moifyied phone") ;

    }


} // Modify phone
void modifiyCalled (char oldname[])
{
    struct CalledNode* tempcall = headCall ;
    int i=1;
    while(tempcall!=NULL)
    {

       i= strcmpi(tempcall->name,oldname);
        if(i==0)
        strcpy(tempcall->name ,newName);
        tempcall = tempcall->next ;

      }
}
//////////////////////////////////////////////////////Sort Function /////////////////////////////////////

void sortB(char arr[][20],int size)
{
    char temp[25];
    for (int i = 0; i < (size - 1); i++)
  {
    for (int j=0; j < size-1; j++)
    {
      if (strcmp(arr[j],arr[j+1])>0)
       {
        strcpy(temp,arr[j]);
	    strcpy(arr[j],arr[j+1]);
	    strcpy(arr[j+1],temp);
       }
    }

  }
 //  printf("Sorted list in ascending order:\n");

  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
}
void sortByBubble()
{
           struct NameNode *n;
            char menuContact[count()][20] ;
            int  current=0, back = 0 ;
            char ch ;
            struct NameNode* temp=head;


    while(temp !=NULL)
    {
        for (int i = 0 ; i < count(); i++ )
        {

               strcpy(menuContact[i] ,temp -> name );
               temp=temp->next;

        } // for

    } // while

    sortB(menuContact,count());
      do
    {
        system("cls");
        printf("Sorted By Bubble Sort \n");
            if(current<0) current = count()-1;
            else if (current > count()-1) current = 0 ;

            for ( int i=0 ; i < count(); i++)
              {

                  if (i==current)
                    textattr(0x70);
                    gotoxy(10,7+2*i);
                    _cprintf("%s",menuContact[i]);
                    textattr(0x07); // to reset default color
              } // for
    ch= getch();
      switch(ch)
    {

         case -32:
         ch = getch();
                         switch(ch)
                         {

                            case 72: // up
                                 current -- ;
                             break ; // up

                             case 80: // down
                                  current ++ ;
                             break;   // down

                             case 71:
                                 current =0 ;
                             break; // home

                             case 79:
                                 current =count() -1  ;
                             break; // end
                         }// ineer switch
         break; // -32


         case 13:
        back =10 ;
            break;


     } // switch
   }// do
    while (!back) ;
}
void Merge(char arr[][20],int low,int mid,int high)
{
    int nL= mid-low+1;
    int nR= high-mid;

    char** L=malloc(sizeof(char *)*nL);
    char** R=malloc(sizeof(char *)*nR);
    int i;
    for(i=0;i<nL;i++)
    {
        L[i]=malloc(sizeof(arr[low+i]));
        strcpy(L[i],arr[low+i]);
    }
    for(i=0;i<nR;i++)
    {
        R[i]=malloc(sizeof(arr[mid+i+1]));
        strcpy(R[i],arr[mid+i+1]);
    }
    int j=0,k;
    i=0;
    k=low;
    while(i<nL&&j<nR)
    {
        if(strcmp(L[i],R[j])<0)strcpy(arr[k++],L[i++]);
        else strcpy(arr[k++],R[j++]);
    }
    while(i<nL)strcpy(arr[k++],L[i++]);
    while(j<nR)strcpy(arr[k++],R[j++]);

}
void MergeSort(char* arr[],int low,int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSort(arr,low,mid);
        MergeSort(arr,mid+1,high);
        Merge(arr,low,mid,high);
    }
}
  void sortByMerge()
{
           struct NameNode *n;
            char menuContact[count()][20] ;
            int  current=0, back = 0 ;
            char ch ;
            struct NameNode* temp=head;


    while(temp !=NULL)
    {
        for (int i = 0 ; i < count(); i++ )
        {

               strcpy(menuContact[i] ,temp -> name );
               temp=temp->next;

        } // for

    } // while

    MergeSort(menuContact,0,count()-1);
      do
    {
        system("cls");
            printf("Sorted By Merge Sort \n");
            if(current<0) current = count()-1;
            else if (current > count()-1) current = 0 ;

            for ( int i=0 ; i < count(); i++)
              {

                  if (i==current)
                    textattr(0x70);
                    gotoxy(10,7+2*i);
                    _cprintf("%s",menuContact[i]);
                    textattr(0x07); // to reset default color
              } // for
    ch= getch();
      switch(ch)
    {

         case -32:
         ch = getch();
                         switch(ch)
                         {

                            case 72: // up
                                 current -- ;
                             break ; // up

                             case 80: // down
                                  current ++ ;
                             break;   // down

                             case 71:
                                 current =0 ;
                             break; // home

                             case 79:
                                 current =count() -1  ;
                             break; // end
                         }// ineer switch
         break; // -32


         case 13:



         back=1;

            break;


     } // switch
   }// do
    while (!back) ;

}



//////////////////////////////////////////////////////Stack Function ////////////////////////////////////
void appendCalled(char name [20])
{
    struct CalledNode * temp ;


     temp = (struct CalledNode*)malloc(sizeof(struct CalledNode )) ;
     strcpy ( temp ->name, name );
     if ( headCall  == NULL)
         {
             headCall = tailCall = temp ;
             temp -> next = NULL ;
             temp -> prev = NULL ;

         } // head == null

         else
         {
             temp-> next = NULL ;
             temp -> prev = tailCall ;
             tailCall -> next = temp ;
             tailCall = temp ;
         }
} // append  call

void displayList()
{
    struct CalledNode *tmp;
    if(headCall== NULL)
    {
        printf(" List is empty.");
    }
    else
    {
        tmp = tailCall;
        while(tmp != NULL)
        {
            printf("%s \n", tmp->name);       // prints the data of current node
            tmp = tmp->prev;                     // advances the position of current node
        }
    }
}


//////////////////////////////////////////////////////Other Function /////////////////////////////////////
int count ( )
{
      int c = 0 ;
    struct NameNode * temp = head ;
    while (temp != NULL  )
    {
       c++ ;
       temp = temp -> next ;
    } // while

    return c ;
} // count

//////////////////////////////////////////////////////Menu Function /////////////////////////////////////
void appendMenu()
{
   system("cls");
                          char name[10];
                          char namer [20] ;
                           do
                           {
                           printf("Enter the name of contact and press enter: ");
                           _flushall();
                           gets(namer);
                           }while(strlen(namer)<10||strlen(namer)>20);
                           appendName(namer);
                           char number[11] ;
                           do
                           {
                           printf("Enter the phone of contact  and press enter: ");
                           scanf("%s",&number);
                           }
                           while (strlen(number)!=11);
                           appendPhone(number,GetIdentity());
                           int x =0 ;
                           do
                           {
                           printf("if you need to add another phone press 0 : ") ;
                           scanf("%d",&x);
                           if ( x == 0 )
                           {

                            char number[11] ;
                           do
                           {
                           printf("Enter the phone of contact  and press enter: ");
                           scanf("%s",&number);
                           }
                           while (strlen(number)!=11);
                           appendPhone(number,GetIdentity());
                           } // if
                        } // do
                        while (!x) ;
                        system("cls");
} // append menu
void appendNewPhone ()
{
    printf("Please enter name To add phone to it:");
    char name[20];
    _flushall();
    gets(name);
    struct NameNode* temp = search_by_name(name);
    if ( temp == NULL)
        printf("There is no Name withe the same");
    else
    {
                  char number [11];
          do
                           {
                           printf("Enter the phone of contact  and press enter: ");

                           scanf("%s",&number);
                           }
                           while (strlen(number)!=11);
                           appendPhone(number,temp->id);
                           printf("Done added phone");

    } //




}
void searchMenu()
{
    char maun[3][30]= {"Search By Name","Search By Phone Number","Back"},ch;
    int i,current=0,flag=0;
    do
    {
        system("cls");

        for(i=0; i<3; i++)
        {
            gotoxy(40,10+2*i);
            if(i==current)
                textattr(0x70);
            _cprintf("%s",maun[i]);
            textattr(15);
        }
        ch=getch();
        switch(ch)
        {
        case -32:
            ch=getch();
            switch(ch)
            {
            case up:
                if(current==0)
                    current=2;
                else
                    current--;
                break;
            case down:
                if(current==2)
                    current=0;
                else
                    current++;
                break;
            case home:
                current=0;
                break;
            case end:
                 current=2;
                break;
            }
            break;
        case enter:
            switch(current)
            {
            case 0:  // Search by Name.
                system("cls");
                  printf("Please enter name to search and press Enter : ");
                             _flushall();
                             char name[20];
                             gets(name) ;
                             struct NameNode * getid;
                             getid=search_by_name(name) ;
                             if( getid == NULL)
                             printf("Name Not Found !!!");
                             else
                             {
                                displayAllname(getid->id);
                                displayAllPhone(getid->id);
                             } // else
                getch();
            break; // Search by Name.

            case 1:  // Search by Phone Number.
                system("cls");
                system("cls");
                              printf("Enter your  number to search and press Enter  :");
                              _flushall();
                                char number[11];
                             gets(number) ;
                             getid=search_by_number(number) ;
                             if( getid == NULL)
                                printf("Number Not Found !!!");
                             else
                             {
                                  displayAllname(getid->id);
                                  displayAllPhone(getid->id);
                             } // else
                getch();
            break;  // Search by Phone Number.

            case 2: // Back.
                flag=44;
            break; // Back.

            }
            break;

        case esc://
            flag=11;
        break;
        }
    }
    while(flag==0);
}

void deleteMenu()
{
     char maun[3][30]= {"Delete By Name","Delete By Phone Number","Back"},ch;
    int i,current=0,flag=0;
    do
    {
        system("cls");
        for(i=0; i<3; i++)
        {
            gotoxy(40,10+2*i);
            if(i==current)
                textattr(0x70);
            _cprintf("%s",maun[i]);
            textattr(15);
        }
        ch=getch();
        switch(ch)
        {
        case -32:
            ch=getch();
            switch(ch)
            {
            case up:
                if(current==0)
                    current=2;
                else
                    current--;
                break;
            case down:
                if(current==2)
                    current=0;
                else
                    current++;
                break;
            case home:
                current=0;
                break;
            case end:
                break;
            }
            break;
        case enter:
            switch(current)
            {
            case 0: //Delete By Name
                system("cls");
                printf("Enter the name  to delete it and press Enter  :");
                char namedelete[20] ;
                _flushall();
                gets(namedelete);
                deletebyname(namedelete);
                getch();
            break; //Delete By Name

            case 1: //Delete By Phone Number
                system("cls");
                 printf("Enter the number  to delete it and press Enter  :");
                char numberdelete[11] ;
                scanf("%s",&numberdelete);
                deletebyphone(numberdelete);
                getch();
            break;  //Delete By Phone Number

            case 2: // Back
                flag=44;
            break; // Back
            }
            break;
        case esc:
            flag=11;
            break;
        }
    }
    while(flag==0);
}

void modifyMenu()
{
     char maun[3][30]= {"Modify Name","Modify Phone Number","Back"},ch;
    int i,current=0,flag=0;
    do
    {
        system("cls");
        for(i=0; i<3; i++)
        {
            gotoxy(40,10+2*i);
            if(i==current)
                textattr(0x70);
            _cprintf("%s",maun[i]);
            textattr(15);
        }
        ch=getch();
        switch(ch)
        {
        case -32:
            ch=getch();
            switch(ch)
            {
            case up:
                if(current==0)
                    current=2;
                else
                    current--;
                break;
            case down:
                if(current==2)
                    current=0;
                else
                    current++;
                break;
            case home:
                current=0;
                break;
            case end:
                break;
            }
            break;
        case enter:
            switch(current)
            {
            case 0:           //Modify Name.
                system("cls");
                 printf("enter the name to modfiy and press Enter : " );
                _flushall();
                char namer[20];
                gets(namer);
               modifyName(namer);
               modifiyCalled(namer);


                getch();
            break;        // Modify Name.

            case 1:  // Modify Number.
                system("cls");
                printf("enter the number to modfiy and press Enter :" );
                char number[11];
                 _flushall();
                gets(number);
                modifyPhone(number);
                getch();
            break; // Modify Number.

            case 2: //Back
                flag=44;
            break; //Back

            }
            break;
        case esc:
            flag=11;
            break;
        }
    }
    while(flag==0);
}

void sortMenu()
{
     char maun[3][16]= {"Merge Sort","Bubble Srot","Back"},ch;
    int i,current=0,flag=0;
    do
    {
        system("cls");
        for(i=0; i<3; i++)
        {
            gotoxy(40,10+2*i);
            if(i==current)
                textattr(0x70);
            _cprintf("%s",maun[i]);
            textattr(15);
        }
        ch=getch();
        switch(ch)
        {
        case -32:
            ch=getch();
            switch(ch)
            {
            case up:
                if(current==0)
                    current=2;
                else
                    current--;
                break;
            case down:
                if(current==2)
                    current=0;
                else
                    current++;
                break;
            case home:
                current=0;
                break;
            case end:
                break;
            }
            break;
        case enter:
            switch(current)
            {
            case 0:                  //  StartMerge Sort
                system("cls");
                sortByMerge();
              //  getch();
            break;                  //End Merge Sort

            case 1:               //Start Bubble Srot
                system("cls");
                sortByBubble();
              //  getch();
            break;              //End ubble Srot

            case 2:            //Start Back
                flag=44;
            break;            //End Back
            }

            break;
        case esc:
            flag=11;
            break;
        }
    }
    while(flag==0);
}

void menu ()
{


            char menu[9][30] = {"Add New Contact","Add New Phone","Display All CONTACT","Search","Delete","Modify","Sort","Called phone","Exit"} ;
            int i, current=0, exitFlag = 0 ;
            char ch ;


    do
    {
        { //  only /to close by code block
          system("cls");
          textattr(0x74);
          gotoxy(40,0);
          printf("Welcome to phone Book...\n ");
          gotoxy(18 ,1);
          textattr(0x75);
          printf("Team Member: 1)Ahmed Hamdy 2)ALaa Rafat 3)Ereny Karam  4)Peter George");
          textattr(0x07);
        } //  only to close by code block

            if(current<0) current = 8;
            else if (current > 8) current = 0 ;
            for ( i=0 ; i<9; i++)
              {

                  if (i==current)
                    textattr(0x101);
                    gotoxy(40,7+2*i);
                    _cprintf("%s",menu[i]);
                    textattr(0x07); // to reset default color
              } // for

     ch= getch();
     switch(ch)
     {

         case -32:
         ch = getch();
                         switch(ch)
                         {

                            case 72: // up
                                 current -- ;
                             break ; // up

                             case 80: // down
                                  current ++ ;
                             break;   // down

                             case 71:
                                 current =0 ;
                             break; // home

                             case 79:
                                 current =8 ;
                             break; // end
                         }// ineer switch
         break; // -32



         case 13:

                     switch(current)
                     {
                       case 0:                    // Add New Contact.
                           /// (1) add name ,,,,, (2) add phone ,,,,, (3) choose to add new phone press y if no end
                           appendMenu();
                       break;                 //Add New Contact.

                       case 1:               //Add New Phone.
                             system("cls");
                           appendNewPhone();
                           getch();

                       break ;              //Add New Phone.

                       case 2:             //Display All CONTACT.
                           system("cls");
                            printf("Display all... \n");
                            displayAllNameMenu() ;
                       break ;            //Display All CONTACT.

                       case 3:           //Search Menu.
                           searchMenu();
                       break ;          //Search Menu.

                       case 4:         //Delete Menu.
                           deleteMenu();
                       break ;        //Delete Menu.

                       case 5:       //Modify Menu.
                           modifyMenu();
                       break;       //Modify Menu.

                       case 6:       //Sort Menu.
                           sortMenu();
                       break;       //Sort Menu.

                       case 7:     //Called Phone.
                            system("cls");
                             displayList();
                            getch();
                       break ;    //Called Phone.

                       case 8 :  //Exit.
                             exitFlag = 1 ;
                       break ;  //Exit.




                } // switch current
        break ; // press enter case 13

        case 79 :
             exitFlag =1;
        break ;

     } // switch

   } // do
    while (!exitFlag);

} // menu


int main()
{

     menu();
}
