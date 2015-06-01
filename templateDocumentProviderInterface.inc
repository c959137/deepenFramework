<?php
/**
* 
*/
namespace m5D02F22739AA11E4B3C6005056847E34;

\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('templateDocumentProviderModeConstantClass', 'constants');

interface templateDocumentProviderInterface
{
}

/**
* 提供套版類別需要的資料介面
*/
interface templateDocumentProvider1Interface extends templateDocumentProviderInterface
{
	/**
	* @brief 取得指定路徑的值
	* @param \m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance 樣板實體
	* @param \m5D02F22739AA11E4B3C6005056847E34\constants\templateDocumentProviderModeConstantClass $providerMode 樣板類型
	* @param string path 相對位置的目錄陣列
	* @param out string $rawData 動態的原始資料
	* @return boolean true 是客制內容不再進行套版動作, false 不是客制內容需執行套版動作
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	public function queryValue(
		\m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance, 
		$providerMode, 
		$path, 
		&$rawData
	);
}

/**
* 提供套版類別需要的資料介面
*/
interface templateDocumentProvider2Interface extends templateDocumentProviderInterface
{
	/**
	* @brief 取得指定路徑的值
	* @param \m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance 樣板實體
	* @param \m5D02F22739AA11E4B3C6005056847E34\constants\templateDocumentProviderModeConstantClass $providerMode 樣板類型
	* @param string $labelName 標籤名稱
	* @param out string $rawData 動態的原始資料
	* @return boolean true 是客制內容不再進行套版動作, false 不是客制內容需執行套版動作
	* @author nico chen 2015-04-09
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-04-09</b>    
	*      - 建立函數			
	*/
	public function queryValue(
		\m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance, 
		$providerMode, 
		$providerName, 
		&$rawData
	);
}
