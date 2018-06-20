#ifndef __MALLOC_H
#define __MALLOC_H
#include "sys.h" 
#ifndef NULL
#define NULL 0
#endif

#define SRAMCCM  0		//CCM内存池(此部分SRAM仅仅CPU可以访问!!!)

#define SRAMBANK 1	    //定义支持的SRAM块数.
		 
//mem3内存参数设定.mem3处于CCM,用于管理CCM(特别注意,这部分SRAM,仅CPU可以访问!!)
#define MEM3_BLOCK_SIZE			64  	  						//内存块大小为64字节
#define MEM3_MAX_SIZE			60 *1024  						//最大管理内存60K
#define MEM3_ALLOC_TABLE_SIZE	MEM3_MAX_SIZE/MEM3_BLOCK_SIZE 	//内存表大小
		 

//内存管理控制器
struct _m_mallco_dev
{
	void (*init)(u8);					//初始化
	u16 (*perused)(u8);		  	    	//内存使用率
	u8 	*membase[SRAMBANK];				//内存池 管理SRAMBANK个区域的内存
	u32 *memmap[SRAMBANK]; 				//内存管理状态表
	u8  memrdy[SRAMBANK]; 				//内存管理是否就绪
};
extern struct _m_mallco_dev mallco_dev;	 //在mallco.c里面定义

void mymemset(void *s,u8 c,u32 count);	//设置内存
void mymemcpy(void *des,void *src,u32 n);//复制内存     
void my_mem_init(u8 memx);				//内存管理初始化函数(外/内部调用)
u32 my_mem_malloc(u8 memx,u32 size);	//内存分配(内部调用)
u8 my_mem_free(u8 memx,u32 offset);		//内存释放(内部调用)
u16 my_mem_perused(u8 memx) ;			//获得内存使用率(外/内部调用) 
////////////////////////////////////////////////////////////////////////////////
//用户调用函数
void myfree(u8 memx,void *ptr);  			//内存释放(外部调用)
void *mymalloc(u8 memx,u32 size);			//内存分配(外部调用)
void *myrealloc(u8 memx,void *ptr,u32 size);//重新分配内存(外部调用)

/*用于wolfssl*/
void *pvPortWolfSSLMalloc( size_t xWantedSize ); 
void pvPortWolfSSLFree( void *pv );
void *pvPortWolfSSLRealloc( void *pv, size_t size );
void pvPortWolfSSLHeapInit( void );
#endif













