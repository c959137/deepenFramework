<?php
namespace m5D02F22739AA11E4B3C6005056847E34\application;

use \m5D02F22739AA11E4B3C6005056847E34\commandPlugins\helpCommandClass as helpCommandClass;
use \m5D02F22739AA11E4B3C6005056847E34\application\applicationAbstractClass as applicationAbstractClass;

/**
* @brief 命令列應用類別
*/
class consoleApplicationClass extends applicationAbstractClass
{
	private static $_staticParams = [];
	
	private $_instanceParams = [
		'propertys' => [
		]
	];
	
	public static function registerCommand($commandName, $commandClass)
	{
		$keyName = 'commands';
		if (!isset(self::$_staticParams[$keyName][$commandName])) {
			self::$_staticParams[$keyName][$commandName] = [
				'class' => $commandClass,
				'instance' => null,
			];
		}
	}

	public static function commandClassList()
	{
		$keyName = 'commands';
		$list = [];
		foreach (self::$_staticParams[$keyName] as $commandName => $info) {
			$list [$commandName] = $info['class'];
		}
		return $list;
	}
	
	
	protected static function commandInstanceByName($commandName)
	{
		$keyName = 'commands';
		if (isset(self::$_staticParams[$keyName][$commandName])) {
			$commandInfo = &self::$_staticParams[$keyName][$commandName]; 
			if (!$commandInfo['instance']) {
				$commandInfo['instance'] = new $commandInfo['class']();
			}
			return $commandInfo['instance'];
		} else {
			throw new \exception("命令 [{$commandName}] 不存在");
		}
	}

	public static function execute()
	{
		if (!isset($_SERVER['argv'][1])) {
			$_SERVER['argv'][1] = 'help';
		}
			
		$commandName = $_SERVER['argv'][1];
		try {
			$commandInstance = static::commandInstanceByName($commandName);
		} catch (\exception $exceptionInstance) {
			echo "{$exceptionInstance->getMessage()}\n";
			$commandInstance = static::commandInstanceByName('help');
			
		}
		$commandInstance->execute();
	}
	
}
consoleApplicationClass::registerCommand('help', '\m5D02F22739AA11E4B3C6005056847E34\commandPlugins\helpCommandClass');