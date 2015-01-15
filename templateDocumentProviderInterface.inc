<?php
/**
* 
*/
namespace m5D02F22739AA11E4B3C6005056847E34;

/**
* 提供套版類別需要的資料介面
*/
interface templateDocumentProviderInterface
{
	/**
	* @brief 取得指定路徑的值
	* @param \m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance 樣板實體
	* @param string path 相對位置的目錄陣列
	* @return mixed
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	public function queryValue(\m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance, $path);
}
