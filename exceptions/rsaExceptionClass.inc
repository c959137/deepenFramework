<?php
namespace m5D02F22739AA11E4B3C6005056847E34\exceptions;

class rsaExceptionClass extends \exception
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;

	private static $_staticParams = [];
	private $_instanceParams = [];
	
	public function __construct ($msg)
	{
		parent::__construct($msg);
	}
}