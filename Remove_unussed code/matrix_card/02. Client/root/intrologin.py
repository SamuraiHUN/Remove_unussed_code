Search and delete:

RUNUP_MATRIX_AUTH = False

Search and delete:

	RUNUP_MATRIX_AUTH = True

Search and delete:

def IsRunupMatrixAuth():
	global RUNUP_MATRIX_AUTH
	return RUNUP_MATRIX_AUTH

Search and delete:

		self.matrixInputChanceCount = 0

Search and delete:

			"WRONGMAT" : localeInfo.LOGIN_FAILURE_WRONG_MATRIX_CARD_NUMBER,
			"QUIT" : localeInfo.LOGIN_FAILURE_WRONG_MATRIX_CARD_NUMBER_TRIPLE,

Search and delete.

			"WRONGMAT" : self.__DisconnectAndInputMatrix,

Search and delete:

		# RUNUP_MATRIX_AUTH
		self.matrixQuizBoard = None
		self.matrixAnswerInput = None
		self.matrixAnswerOK = None
		self.matrixAnswerCancel = None
		# RUNUP_MATRIX_AUTH_END

Search and delete:

	def __DisconnectAndInputMatrix(self):
		if self.connectingDialog:
			self.connectingDialog.Close()
		self.connectingDialog = None

		self.stream.popupWindow.Close()
		self.matrixInputChanceCount -= 1

		if self.matrixInputChanceCount <= 0:
			self.__OnCloseInputDialog()

		elif self.inputDialog:
			self.inputDialog.Show()

Search and delete:

			# RUNUP_MATRIX_AUTH
			if IsRunupMatrixAuth():
				self.matrixQuizBoard = GetObject("RunupMatrixQuizBoard")
				self.matrixAnswerInput = GetObject("RunupMatrixAnswerInput")
				self.matrixAnswerOK = GetObject("RunupMatrixAnswerOK")
				self.matrixAnswerCancel = GetObject("RunupMatrixAnswerCancel")
			# RUNUP_MATRIX_AUTH_END

Search and delete:

		# RUNUP_MATRIX_AUTH
		if IsRunupMatrixAuth():
			self.matrixAnswerOK.SAFE_SetEvent(self.__OnClickMatrixAnswerOK)
			self.matrixAnswerCancel.SAFE_SetEvent(self.__OnClickMatrixAnswerCancel)
			self.matrixAnswerInput.SAFE_SetReturnEvent(self.__OnClickMatrixAnswerOK)
		# RUNUP_MATRIX_AUTH_END

Search and delete:

	# RUNUP_MATRIX_AUTH
	def BINARY_OnRunupMatrixQuiz(self, quiz):
		if not IsRunupMatrixAuth():
			return

		id = self.GetChild("RunupMatrixID")
		id.SetText(self.idEditLine.GetText())

		code = self.GetChild("RunupMatrixCode")

		code.SetText("".join(["[%c,%c]" % (quiz[i], quiz[i+1]) for i in xrange(0, len(quiz), 2)]))

		self.stream.popupWindow.Close()
		self.serverBoard.Hide()
		self.connectBoard.Hide()
		self.loginBoard.Hide()
		self.matrixQuizBoard.Show()
		self.matrixAnswerInput.SetFocus()

	def __OnClickMatrixAnswerOK(self):
		answer = self.matrixAnswerInput.GetText()

		print "matrix_quiz.ok"
		net.SendRunupMatrixCardPacket(answer)
		self.matrixQuizBoard.Hide()

		self.stream.popupWindow.Close()
		self.stream.popupWindow.Open("WAITING FOR MATRIX AUTHENTICATION", 
			self.__OnClickMatrixAnswerCancel, 
			localeInfo.UI_CANCEL)

	def __OnClickMatrixAnswerCancel(self):
		print "matrix_quiz.cancel"

		if self.matrixQuizBoard:
			self.matrixQuizBoard.Hide()

		if self.connectBoard:
			self.connectBoard.Show()

		if self.loginBoard:
			self.loginBoard.Show()

	# RUNUP_MATRIX_AUTH_END

Search and delete:

	def OnMatrixCard(self, row1, row2, row3, row4, col1, col2, col3, col4):
		if self.connectingDialog:
			self.connectingDialog.Close()
		self.connectingDialog = None

		self.matrixInputChanceCount = 3

		self.stream.popupWindow.Close()

		# CHINA_MATRIX_CARD_BUG_FIX
		## A~Z ±îÁö 26 ŔĚł»ŔÇ °ŞŔĚ µéľîŔÖľîľß¸¸ ÇŃ´Ů.
		## Python Exception Log żˇĽ­ ±× ŔĚ»óŔÇ °ŞŔĚ µéľîŔÖľîĽ­ żˇ·Ż ąćÁö
		## ÇĺµĄ żÖ ÇŃ±ąÂĘ ·Î±×żˇĽ­ ŔĚ°Ô Č°żëµÇ´ÂÁö´Â ¸đ¸Ł°ÚŔ˝
		row1 = min(30, row1)
		row2 = min(30, row2)
		row3 = min(30, row3)
		row4 = min(30, row4)
		# END_OF_CHINA_MATRIX_CARD_BUG_FIX

		row1 = chr(row1 + ord('A'))
		row2 = chr(row2 + ord('A'))
		row3 = chr(row3 + ord('A'))
		row4 = chr(row4 + ord('A'))
		col1 = col1 + 1
		col2 = col2 + 1
		col3 = col3 + 1
		col4 = col4 + 1

		inputDialog = uiCommon.InputDialogWithDescription2()
		inputDialog.SetMaxLength(8)
		inputDialog.SetAcceptEvent(ui.__mem_func__(self.__OnAcceptMatrixCardData))
		inputDialog.SetCancelEvent(ui.__mem_func__(self.__OnCancelMatrixCardData))
		inputDialog.SetTitle(localeInfo.INPUT_MATRIX_CARD_TITLE)
		inputDialog.SetDescription1(localeInfo.INPUT_MATRIX_CARD_NUMBER)
		inputDialog.SetDescription2("%c%d %c%d %c%d %c%d" % (row1, col1, row2, col2, row3, col3, row4, col4))

		inputDialog.Open()
		self.inputDialog = inputDialog

	def __OnAcceptMatrixCardData(self):
		text = self.inputDialog.GetText()
		net.SendChinaMatrixCardPacket(text)
		if self.inputDialog:
			self.inputDialog.Hide()
		self.PopupNotifyMessage(localeInfo.LOGIN_PROCESSING)
		return True

	def __OnCancelMatrixCardData(self):
		self.SetPasswordEditLineFocus()
		self.__OnCloseInputDialog()
		self.__DisconnectAndInputPassword()
		return True

Search and delete:

		self.stream.popupWindow.Open(localeInfo.LOGIN_FAILURE_WRONG_MATRIX_CARD_NUMBER_TRIPLE, app.Exit, localeInfo.UI_OK)

Search and delete:

		# RUNUP_MATRIX_AUTH
		if IsRunupMatrixAuth():
			self.matrixQuizBoard.Hide()
		# RUNUP_MATRIX_AUTH_END

Search and delete:

		# RUNUP_MATRIX_AUTH
		if IsRunupMatrixAuth():
			self.matrixQuizBoard.Hide()
		# RUNUP_MATRIX_AUTH_END
