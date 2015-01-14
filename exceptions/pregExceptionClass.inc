<?php
namespace m5D02F22739AA11E4B3C6005056847E34\exceptions;

class pregExceptionClass extends \exception
{
	use \m5D02F22739AA11E4B3C6005056847E34\propertysClass;
	private static $_staticParams = [
		'errors' => [
			PREG_INTERNAL_ERROR => '内部错误',
			PREG_BACKTRACK_LIMIT_ERROR => '超出回溯限制',
			PREG_RECURSION_LIMIT_ERROR => '超出递归限制',
			PREG_BAD_UTF8_ERROR => '异常的utf-8数据',
			PREG_BAD_UTF8_OFFSET_ERROR => '偏移量与urf-8長度不相符',
		]
	];
	
	public function __construct ($errorCode)
	{
		var_dump($errorCode);
		self::$_staticParams['propertys']['errorCode'] = $errorCode;
		parent::__construct('正規式發生錯誤:' . self::$_staticParams['errors'][$errorCode]);
	}
}