<?php
namespace m5D02F22739AA11E4B3C6005056847E34;
require 'moduleManagerAbstractClass.inc';
class moduleManagerClass extends moduleManagerAbstractClass
{
	private static $_staticParams = [];
	private $_instanceParams = [];
	
	protected function actualPathGet()
	{
		return __FILE__;
	}
}
