#ifndef __SCREEN_H__
#define __SCREEN_H__


//页面索引
typedef enum{
	PAGE_HOME=0,
	PAGE_RANGE=1,
	PAGE_END,
}ScreenPage;

extern ScreenPage pageIndex;
//切换下一个页面
void ScreenPage_NextPage(void);

//阈值索引
typedef enum{
	RANGE_EDIT_TEMPERATURE_MIN = 0,
	RANGE_EDIT_TEMPERATURE_MAX = 1,
    RANGE_EDIT_HUMIDITY_MIN = 2,   
    RANGE_EDIT_HUMIDITY_MAX = 3,
	RANGE_EDIT_END,
}RangeEditIndex;

extern RangeEditIndex rangeEditIndex;
//切换下一个阈值编辑项
void RangeEditIndex_Next(void);
//切换上一个阈值编辑项
void RangeEditIndex_Prev(void);

//编辑状态索引
typedef enum{
	RANGE_EDIT_STATE_NORMAL = 0,
	RANGE_EDIT_STATE_EDITING = 1,
}RangeEditState;

extern RangeEditState rangeEditState;
//进入阈值编辑状态
void RangeEditState_EnterEditing(void);
//退出阈值编辑状态
void RangeEditState_QuitEditing(void);
//切换阈值编辑项
void RangeEditState_Toggle(void);
#endif 
