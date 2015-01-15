<?php
/**
* @file  
* 頁面類別
*/

namespace m5D02F22739AA11E4B3C6005056847E34\pages;
/**
* 抽象頁面類別
*/
abstract class pageAbstractClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\propertysClass;
	/**
	* @brief 建構式
	* @use onCreate
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	public function __construct ()
	{
		$this->onCreate();
	}
	abstract protected function onCreate();
	
	/**
	* @brief 解構式
	* @use onDestroy
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	public function __destruct()
	{
		$this->onDestroy();
	}
	abstract protected function onDestroy();
}

