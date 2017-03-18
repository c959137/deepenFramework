<?php
namespace m5D02F22739AA11E4B3C6005056847E34\traits;

trait rsaUtilsClass 
{
	/*
		平台公鑰解密
	**/	
	public static function decrypt($response, $privateKey)
	{
		$crypto = '';
		foreach (str_split(base64_decode($response), 128) as $chunk) 
		{
			openssl_private_decrypt($chunk, $decryptData, $privateKey);
			$crypto .= $decryptData;
		}
		return $crypto;
	}
	
	/*
		平台公鑰加密
	**/	
	public static function encrypt($paramsStr, $publicKey)
	{
		$encryptData = '';
		foreach (str_split($paramsStr, 117) as $chunk){
			openssl_public_encrypt($chunk, $encrypted, $publicKey);
			$encryptData .= $encrypted;
		}
		return base64_encode($encryptData);
	}
	
	/**
		* RSA加签
		* @param $paramStr
		* @return string
	*/
	public static function sign($paramStr, $privateKey)
	{
		openssl_sign($paramStr, $sign, $privateKey);
		return base64_encode($sign);
	}

	/**
		* 验签
		* @param $data
		* @param $sign
		* @return int
	*/
	public static function verify($data, $sign, $publicKey)
	{
		$publicKey = openssl_get_publickey($publicKey);
		$sign = base64_decode($sign);
		if (!(bool)openssl_verify($data, $sign, $publicKey)) {
			throw new \exception("驗證簽名錯誤");
		};
	}
}