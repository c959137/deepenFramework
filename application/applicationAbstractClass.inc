<?php
namespace m5D02F22739AA11E4B3C6005056847E34\application;
/**
* @brief 應用類別
*/
abstract class applicationAbstractClass 
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	
	private static $_staticParams = [];
	private $_instanceParams = [];

	/**
	* @brief 取得框架實體
	* @return object 
	*/
	public static function instance()
	{
		$keyName = __FUNCTION__;
		$className = get_called_class();
		if (!isset(self::$_staticParams[$keyName][$className])) {
			self::$_staticParams[$keyName][$className] = new $className();
		}
		return self::$_staticParams[$keyName][$className];
	}
}