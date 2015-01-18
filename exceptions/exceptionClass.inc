<?php
namespace m5D02F22739AA11E4B3C6005056847E34\exceptions;
abstract class exceptionClass extends \exception
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private static $_staticParams = [];
	private $_instanceParams = [];
}