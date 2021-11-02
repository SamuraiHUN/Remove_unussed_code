search this:

		else:
			connectingIP = self.stream.GetConnectAddr()
			if connectingIP:
				'''
				if app.GetLoginType() == app.LOGIN_TYPE_NONE:
					self.__OpenLoginBoard()
					if IsFullBackImage():
						self.GetChild("bg1").Hide()
						self.GetChild("bg2").Show()
				else:
					self.__RefreshServerList()
					self.__OpenServerBoard()
				'''
				if app.USE_OPENID and not app.OPENID_TEST:
					self.__RefreshServerList()
					self.__OpenServerBoard()
				else:
					self.__OpenLoginBoard()
					if IsFullBackImage():
						self.GetChild("bg1").Hide()
						self.GetChild("bg2").Show()
			else:
				self.__RefreshServerList()
				self.__OpenServerBoard()

change to:

		else:
			connectingIP = self.stream.GetConnectAddr()
			if connectingIP:
				'''
				if app.GetLoginType() == app.LOGIN_TYPE_NONE:
					self.__OpenLoginBoard()
					if IsFullBackImage():
						self.GetChild("bg1").Hide()
						self.GetChild("bg2").Show()
				else:
					self.__RefreshServerList()
					self.__OpenServerBoard()
				'''
				self.__OpenLoginBoard()
				if IsFullBackImage():
					self.GetChild("bg1").Hide()
					self.GetChild("bg2").Show()
			else:
				self.__RefreshServerList()
				self.__OpenServerBoard()

search this:

		if app.USE_OPENID and not app.OPENID_TEST:
			## 2012.07.19 OpenID : ±čżëżí
			# Ă¤łÎ Ľ±ĹĂ Č­¸éżˇĽ­ "Č®ŔÎ"(SelectServerButton) Ŕ» ´­·¶Ŕ»¶§,
			# ·Î±×ŔÎ Č­¸éŔ¸·Î łŃľî°ˇÁö ľĘ°í ąŮ·Î Ľ­ąöżˇ OpenID ŔÎÁőĹ°¸¦ ş¸ł»µµ·Ď ĽöÁ¤
			self.stream.SetConnectInfo(ip, tcp_port, account_ip, account_port)
			self.Connect(0, 0)
		else:
			self.stream.SetConnectInfo(ip, tcp_port, account_ip, account_port)
			self.__OpenLoginBoard()

change to:

		self.stream.SetConnectInfo(ip, tcp_port, account_ip, account_port)
		self.__OpenLoginBoard()