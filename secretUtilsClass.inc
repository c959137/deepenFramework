<?php
namespace m5D02F22739AA11E4B3C6005056847E34;

/**
	加密工具類別
	
	cast-128 gost rijndael-128 twofish arcfour cast-256 loki97 rijndael-192 saferplus wake blowfish-compat des rijndael-256 serpent xtea blowfish enigma rc2 tripledes
*/

/***
	.NET RijndaelManaged 物件加密後, php 解碼
	Rijndael 128, ecb, PKCS7
	
		$encodeData = '+nlp5xYwHUPQsKCidIS91fW16/CAHAdYKzN00ZY0VFs=';
		$key = 'abcdefg123456789';
		echo decodeData($encodeData, $key);
		
		>> Member=aaa&Password=bbb
*/

class secretUtilsClass
{
	private $_instanceParams = [];
	public function __construct($algorithm = 'rijndael-128', $mode = 'ecb')
	{
		$this->_instanceParams['algorithm'] = $algorithm; 
		$this->_instanceParams['mode'] = $mode; 
	}
	
	function __destruct()
	{
		$this->stop();
	}
	
	public function start($key, $iv = '')
	{
		if (!isset($this->_instanceParams['cp'])) {
			$cp = mcrypt_module_open($this->_instanceParams['algorithm'], '', $this->_instanceParams['mode'], '');
			$key = substr($key, 0, mcrypt_enc_get_key_size($cp)); 
			if ($iv == '') {
				$iv = mcrypt_create_iv(mcrypt_enc_get_iv_size($cp), MCRYPT_RAND); 
			}
			mcrypt_generic_init($cp, $key, $iv);
			$this->_instanceParams['cp'] = $cp;
		}
	}
	
	public function stop()
	{
		if (isset($this->_instanceParams['cp'])) {
			mcrypt_generic_deinit($this->_instanceParams['cp']);
			mcrypt_module_close($this->_instanceParams['cp']);
			unset($this->_instanceParams['cp']);
		}
	}

	public function encode($data)
	{
		if (!isset($this->_instanceParams['cp'])) {
			throw new \exception('請先啟動');
		}
		return base64_encode (mcrypt_generic($this->_instanceParams['cp'], $data));
	}
	
	public function decode($data)
	{
		if (!isset($this->_instanceParams['cp'])) {
			throw new \exception('請先啟動');
		}
		return mdecrypt_generic($this->_instanceParams['cp'], base64_decode($data));
	}	
}