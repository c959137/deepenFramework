<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases;
abstract class recordsetAbstractClass
{
	use	\m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [];
	public function __construct()
	{
	}
	
	public function fetchRow()
	{
		return $this->doFetchRow();
	}
	abstract protected function doFetchRow();
	
	abstract protected function recordCountGet();
	
	protected function affectedRows()
	{
		return 0;
	}
	
	public function nextRowset()
	{
		return false;
	}
}
