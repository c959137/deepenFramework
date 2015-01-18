<?php
/**
* @file  
* 框架主檔
*/

namespace m5D02F22739AA11E4B3C6005056847E34\traits;

/**
* 屬性類別
*/
trait constantCheckerClass 
{
	protected static function constantChecker($staticArrayKeyName, $constantName)
	{
		if (!isset(self::$_staticParams[$staticArrayKeyName][$constantName])) {
			$constantNotExistsExceptionClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('constantNotExistsExceptionClass', 'exceptions');
			throw new $constantNotExistsExceptionClass(__CLASS__, $constantName);
		}
	}
}
