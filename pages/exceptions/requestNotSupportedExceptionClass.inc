<?php
namespace m5D02F22739AA11E4B3C6005056847E34\pages\exceptions;

use \m5D02F22739AA11E4B3C6005056847E34\exceptions\exceptionClass as exceptionClass;

class requestNotSupportedExceptionClass extends exceptionClass
{
	private static $_staticParams = [];
	private $_instanceParams = [];

	public function __construct ($methodName)
	{
		$this->_instanceParams['methodName'] = $methodName;
		parent::__construct("不支援指定的請求");
	}
	
	protected function methodNameGet()
	{
		$keyName = static::propMethodNameToKeyName(__FUNCTION__);
		return $this->_instanceParams[$keyName];
	}
}