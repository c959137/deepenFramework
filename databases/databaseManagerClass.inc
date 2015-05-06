<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases;
class databaseManagerClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\arrayPathClass;

	const CONNECTION_TYPE_PDO = 'pdo';
	private static $_staticParams = [];
	
	public static function connectionInstance($connectionName, $connectionType = self::CONNECTION_TYPE_PDO, $connectionInformation)
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = [];
		}
		
		if (!isset(self::$_staticParams[$keyName][$connectionName])) {
			switch ($connectionType) {
				case self::CONNECTION_TYPE_PDO :
					$className = static::classLoader('connectionClass', 'pdo');
					break;
					
				default : 
					xxx();
					break;
			}
			self::$_staticParams[$keyName][$connectionName] = [
				'instance' => new $className($connectionInformation),
			];
		}
		return self::$_staticParams[$keyName][$connectionName]['instance'];
	}

	protected static function classLoader($className, $middleNs = '')
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = [];
		}
		if (!isset(self::$_staticParams[$keyName][$className])) {
			$moduleClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::moduleClassLoaderByPath(__FILE__);
			$middleNs =  static::pathToNs(__FILE__, ['pdo']);
			$fullClassName = $moduleClass::classLoader($className, $middleNs);
			self::$_staticParams[$keyName][$className] = $fullClassName;
		}
		return self::$_staticParams[$keyName][$className];
	}
}
