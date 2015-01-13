<?php
/**
* @file  
* 暫時放置, 有時間再分類
*/
/**
* @brief 設定中斷點, 為了方便使用所以封裝了 backtraceTools::xxx
* @param string $msg 中斷點說明
* @author nico chen 2015-01-08
* @version 0.00.01
* \b CHANGE \b HISTORY: <br>	 
*   <b>- nico chen / 2015-01-08</b>    
*      - 建立函數			
*/
function xxx($msg = '')
{
	$backtraceToolsClass = m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('backtraceToolsClass');
	$backtraceToolsClass::xxx($msg, __FUNCTION__, '');
}
