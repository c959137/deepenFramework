<?php
/*
	網頁資源常數
*/
namespace m5D02F22739AA11E4B3C6005056847E34\constants;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('constantCheckerClass', 'traits');
/*
	資源常數類別
*/
class requestModeConstantClass {
	use \m5D02F22739AA11E4B3C6005056847E34\traits\constantCheckerClass;
	const REQUEST_MODE_POST = 'POST';	
	const REQUEST_MODE_GET = 'GET';
	const REQUEST_MODE_AJAX = 'AJAX';
	private static $_staticParams = [
		'requestModeList' => [
			self::REQUEST_MODE_POST => '',
			self::REQUEST_MODE_GET => '',
			self::REQUEST_MODE_AJAX => '',
		]
	];
	private $_instanceParams = [];
	
	public static function resourceTypeChecker($constantName)
	{
		static::constantChecker('requestModeList', $constantName);
	}
	
}