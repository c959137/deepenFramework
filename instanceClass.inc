<?php
/**
* 取得單一實體的方法
*/

namespace m5D02F22739AA11E4B3C6005056847E34;

trait instanceClass 
{
	/**
	* @brief 取得框架實體
	* @return object 
	*/
	public static function instance()
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = new self();
		}
		return self::$_staticParams[$keyName];
	}
}
