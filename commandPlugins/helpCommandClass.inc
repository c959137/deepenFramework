<?php
namespace m5D02F22739AA11E4B3C6005056847E34\commandPlugins;

use \m5D02F22739AA11E4B3C6005056847E34\commandPlugins\commandPluginClass as commandPluginClass;
use \m5D02F22739AA11E4B3C6005056847E34\application\consoleApplicationClass as applicationClass;

class helpCommandClass extends commandPluginClass
{
	
	protected function doExecute()
	{
		echo "命令系統\n";
		$commandClassList = applicationClass::commandClassList();
		foreach ($commandClassList as $commandName => $commandClass) {
			echo "\t{$commandName}\n\t\t" . $commandClass::help(), "\n";
		}
	}
	
	public static function help()
	{
		return "提供說明";
	}
}
