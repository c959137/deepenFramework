<?php
namespace m5D02F22739AA11E4B3C6005056847E34\commandPlugins;

abstract class commandPluginClass 
{
	public function execute()
	{
		$this->doExecute();
	}
	abstract protected function doExecute();
	
	abstract public static function help();
}