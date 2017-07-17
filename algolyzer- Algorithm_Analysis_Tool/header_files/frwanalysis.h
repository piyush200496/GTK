static gchar* linl=NULL;
static gchar* binl=NULL;
static gchar* ssl=NULL;
static gchar* bsl=NULL;
static gchar* msl=NULL;
static gchar* isl=NULL;
static gchar* qsl=NULL;
static gchar* rqsl=NULL;
static gchar* ans=NULL;
static double lins,bins;
static double ss,bs,is,ms,qs,rqs;
typedef void (*sortf_t)(int*,int);
typedef void (*searchf_t)(int*,int);
const int SORT_TYPES=6, INCOMPATIBLE_SORT_TYPES=3;
const int SEARCH_TYPES=2;
/*
extern const char sortname[][25];
extern const char searchname[][25];
extern const char (*curr_list)[25];
*/
extern int dominatelist[];
extern double timelist[];
extern int curr_no_of_test;
extern int LIST_SIZE;


int cmpf_int(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
void analysis_fprinter(FILE *fpout, double arr[], char opname[][25], const int size)
{
 int i;
 for(i=0; i<size; i++)
   fprintf(fpout,"%s: %fms\n",opname[i],arr[i]);
}
void timer_sortf(sortf_t slist,int *arr,const int size,double *timelist,const int i, double *mintime, int *minpos)
{
	double timeinms;
	clock_t timer=clock();
	(*slist)(arr,size);
	timer=clock()-timer;
	timeinms=(double)timer*1000/CLOCKS_PER_SEC;
	timelist[i]+=timeinms;
	if(timeinms<(*mintime))
	{
		*mintime=timeinms;
		*minpos=i;
	}
}
void fileread_sort(char *filepath)
{
	char sortname[6][25]={"Selection Sort","Bubble Sort","Insertion Sort","Merge Sort","Quick Sort","Randomized Quick Sort"};
	sortf_t sortflist[3]={&selectionSort,&bubbleSort,&insertionSort};
	//double timelist[SORT_TYPES];
        int i,n,t,j,asize,lsize,size,*values[SORT_TYPES];
	for(i=0; i<SORT_TYPES; i++)
	{	
		timelist[i]=0.000;
		dominatelist[i]=0;
	}

        FILE *fpin;
        fpin=fopen(filepath,"r");
        FILE *fpout=fopen("sorting_output_#.txt","w");
        if(fpout==NULL)
        {
                printf("File couldn't be written!\n");
                fclose(fpin);
                fclose(fpout);
                return;
        }

        if(fpin!=NULL)
        {
                if(!feof(fpin))
                        fscanf(fpin,"%d",&t);

		LIST_SIZE=6;
		curr_no_of_test=t;

                while(t--)
                {
                        fscanf(fpin,"%d",&n);
			for(i=0; i<SORT_TYPES; i++)
			{	values[i]=calloc(n,sizeof(int));
                        	if(values[i]==NULL)
                        	{
                                	fprintf(fpout,"Couldn't allocate enough memory!\n");
			                fclose(fpin);
			                fclose(fpout);
	                                return;
	                        }
			}
                        for(i=0; !feof(fpin), i<n; i++)
                        {
                                fscanf(fpin,"%d",&values[0][i]);
				for(j=1; j<SORT_TYPES; j++)
					values[j][i]=values[0][i];
                        }
			
			double mintime=999.999;
			int minpos=0;
			for(i=0; i<SORT_TYPES-INCOMPATIBLE_SORT_TYPES; i++)
				timer_sortf(sortflist[i],values[i],n,timelist,i,&mintime,&minpos);

			clock_t timer=clock();
			double timeinms;
			mergeSort(values[3],0,n-1);
			timer=clock()-timer;
			timeinms=(double)timer*1000/CLOCKS_PER_SEC;		
			timelist[3]+=timeinms;
			if(timeinms<mintime)
			{
				mintime=timeinms;
				minpos=3;
			}
            //ms=timelist[3];
			timer=clock();
			quickSort(values[4],0,n-1);
			timer=clock()-timer;
			timeinms=(double)timer*1000/CLOCKS_PER_SEC;		
			timelist[4]+=timeinms;
			if(timeinms<mintime)
			{
				mintime=timeinms;
				minpos=4;
			}
            //Qs=timelist[4];
			timer=clock();
			qsort(values[5], n, sizeof(int), cmpf_int);
			timer=clock()-timer;
			timeinms=(double)timer*1000/CLOCKS_PER_SEC;		
			timelist[5]+=timeinms;
			if(timeinms<mintime)
			{
				mintime=timeinms;
				minpos=5;
			}
            // qs=timelist[5];
			/*for(i=0; i<SORT_TYPES; i++)
			{
				for(j=0; j<n; j++)
					printf("%d\t",values[i][j]);
				printf("\n\n");
			}*/

			for(i=0; i<SORT_TYPES; i++)
				free(values[i]);

			dominatelist[minpos]++;

		}
		ss=timelist[0];
		bs=timelist[1];
		is=timelist[2];
		ms=timelist[3];
		qs=timelist[4];
		rqs=timelist[5];
		asize=sizeof(timelist)/sizeof(timelist[0]);
		lsize=sizeof(sortname)/25;
		size=(asize<lsize)?asize:lsize;
		analysis_fprinter(fpout,timelist,sortname,size);
                fclose(fpin);
                fclose(fpout);
//              sortresult();
		//curr_list=&sortname[0];
		printf("%d\n",curr_no_of_test);
		chartor();
		return;
        }
        printf(fpout,"File couldn't be read\n");
        fclose(fpin);
        fclose(fpout);
}

void fileread_search(char *filepath)
{
	char searchname[2][25]={"Linear Search","Binary Search"};
	//double timelist[SEARCH_TYPES];
        int i,n,t,j,q,asize,lsize,size,*values[SEARCH_TYPES];
	for(i=0; i<SEARCH_TYPES; i++)
			timelist[i]=0.000;

        FILE *fpin;
        fpin=fopen(filepath,"r");
        FILE *fpout=fopen("searching_output_#.txt","w");
        if(fpout==NULL)
        {
                printf("File couldn't be written!\n");
                fclose(fpin);
                fclose(fpout);
                return;
        }
        if(fpin!=NULL)
        {
                if(!feof(fpin))
                        fscanf(fpin,"%d",&t);
                while(t--)
                {
                        fscanf(fpin,"%d %d",&n,&q);
			for(i=0; i<SEARCH_TYPES; i++)
			{	values[i]=calloc(n,sizeof(int));
                        	if(values[i]==NULL)
                        	{
                                	fprintf(fpout,"Couldn't allocate enough memory!\n");

			                fclose(fpin);
			                fclose(fpout);
	                                return;
	                        }
			}
                        for(i=0; !feof(fpin), i<n; i++)
                        {
                                fscanf(fpin,"%d",&values[0][i]);
				for(j=1; j<SEARCH_TYPES; j++)
					values[j][i]=values[0][i];
                        }

			clock_t timer=clock();
			qsort(values[1], n, sizeof(int), cmpf_int);
			timer=clock()-timer;
			timelist[1]+=(double)timer*1000/CLOCKS_PER_SEC;

			for(i=0; i<q; i++)
			{
				int pos,ele;
                                fscanf(fpin,"%d",&ele);

				timer=clock();
				pos=search(values[0],n,ele);
				timer=clock()-timer;
				timelist[0]+=(double)timer*1000/CLOCKS_PER_SEC;
                //ls=timelist[0];
				timer=clock();
				pos=binarySearch(values[1],0,n,ele);
				timer=clock()-timer;
				timelist[1]+=(double)timer*1000/CLOCKS_PER_SEC;
                //qs=timelist[1];
			}
			lins=timelist[0];
            bins=timelist[1];
			for(i=0; i<SEARCH_TYPES; i++)
				free(values[i]);
		}

		asize=sizeof(timelist)/sizeof(timelist[0]);
		lsize=sizeof(searchname)/25;
		size=(asize<lsize)?asize:lsize;
		analysis_fprinter(fpout,timelist,searchname,size);
                fclose(fpin);
                fclose(fpout);
//                searchresult();
		//LIST_SIZE=2;
		//curr_no_of_test=479;
		//curr_list=&searchname[0];
		chartor();
		return;
        }
        printf(fpout,"File couldn't be read\n");
        fclose(fpin);
        fclose(fpout);
}
