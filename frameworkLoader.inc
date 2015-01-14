<?php
if (defined('frameworkLoader')) {
	return;
};
define('frameworkLoader', '');
class frameworkLoaderClass
{
	const FRAMEWORK_MODULE = 'MODULE_5D02F22739AA11E4B3C6005056847E34';
	const FRAMEWORK_FILENAME = 'applicationFrameworkClass.inc';
	private static $_staticParams = [
		'required' => [
			'APPLICATION_UID' => '應用程式編號',
			'CONFIG_RESOURCES' => '設定資源目錄',
			'DATA_RESOURCES' => '資料資源目錄',
			'LOGGER_RESOURCES' => '紀錄資源目錄',
			'' => '',
		]
	];
	
	protected static function requiredTest()
	{
		$list = [];
		foreach (self::$_staticParams['required'] as $keyName => $keyTitle) {
			if ($keyName == '' || isset($_SERVER[$keyName])) {
				continue;
			}
			$list[$keyName] = $keyTitle;
		}
		if (!empty($list)) {
			echo "必要的環境變數不存在<br/>";
			foreach ($list as $keyName => $keyTitle) {
				echo "{$keyName}[{$keyTitle}] <br/>";
			}
			die();
		}
		if (!isset($_SERVER[self::FRAMEWORK_MODULE])) {
			throw new exception ('框架設定 [' . self::FRAMEWORK_MODULE . '] 不存在');
		}
	}
	public static function execute()
	{
		static::requiredTest();
		$rootPath = $_SERVER[self::FRAMEWORK_MODULE];
		if (substr($rootPath, -1) != DIRECTORY_SEPARATOR) {
			$rootPath .= DIRECTORY_SEPARATOR;
		}
		$path = $rootPath . self::FRAMEWORK_FILENAME;
		if (!file_exists($path)) {
			throw new exception ("框架主檔 [{$path}] 不存在");
		}
		require $path;

		$path = $rootPath . 'utils.inc';
		if (!file_exists($path)) {
			throw new exception ("框架主檔 [{$path}] 不存在");
		}
		require $path;
	}
}
define('applicationFrameworkClass', 'm5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass');
\frameworkLoaderClass::execute();