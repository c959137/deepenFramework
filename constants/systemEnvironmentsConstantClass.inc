<?php
/*
	網頁資源常數
*/
namespace m5D02F22739AA11E4B3C6005056847E34\constants;

/*
	資源常數類別
*/
class systemEnvironmentsConstantClass {
	use \m5D02F22739AA11E4B3C6005056847E34\traits\constantCheckerClass;
	
	const ENV_KEY = 'ENVIRONMENT_TYPE';
	const CONFIG_KEY = 'environmentType';
	
	const DEVELOPMENT = 'DEVELOPMENT';
	const TEST = 'TEST';
	const PRODUCTION = 'PRODUCTION';
	
	private static $_staticParams = [
		'environments' => [
			self::DEVELOPMENT => '開發環境',
			self::TEST => '測試環境',
			self::PRODUCTION => '生產環境',
		]
	];
	
	private $_instanceParams = [];
	
	public static function environmentTypeChecker($constantName)
	{
		static::constantChecker('environments', $constantName);
		return $constantName;
	}
}