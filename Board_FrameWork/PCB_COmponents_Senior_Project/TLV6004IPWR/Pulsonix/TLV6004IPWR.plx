PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//754545/67790/2.31/14/0/Integrated Circuit

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r147.5_45"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.45) (shapeHeight 1.475))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "SOP65P640X120-14N" (originalName "SOP65P640X120-14N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r147.5_45) (pt -2.938, 1.95) (rotation 90))
			(pad (padNum 2) (padStyleRef r147.5_45) (pt -2.938, 1.3) (rotation 90))
			(pad (padNum 3) (padStyleRef r147.5_45) (pt -2.938, 0.65) (rotation 90))
			(pad (padNum 4) (padStyleRef r147.5_45) (pt -2.938, 0) (rotation 90))
			(pad (padNum 5) (padStyleRef r147.5_45) (pt -2.938, -0.65) (rotation 90))
			(pad (padNum 6) (padStyleRef r147.5_45) (pt -2.938, -1.3) (rotation 90))
			(pad (padNum 7) (padStyleRef r147.5_45) (pt -2.938, -1.95) (rotation 90))
			(pad (padNum 8) (padStyleRef r147.5_45) (pt 2.938, -1.95) (rotation 90))
			(pad (padNum 9) (padStyleRef r147.5_45) (pt 2.938, -1.3) (rotation 90))
			(pad (padNum 10) (padStyleRef r147.5_45) (pt 2.938, -0.65) (rotation 90))
			(pad (padNum 11) (padStyleRef r147.5_45) (pt 2.938, 0) (rotation 90))
			(pad (padNum 12) (padStyleRef r147.5_45) (pt 2.938, 0.65) (rotation 90))
			(pad (padNum 13) (padStyleRef r147.5_45) (pt 2.938, 1.3) (rotation 90))
			(pad (padNum 14) (padStyleRef r147.5_45) (pt 2.938, 1.95) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -3.925 2.8) (pt 3.925 2.8) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 3.925 2.8) (pt 3.925 -2.8) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 3.925 -2.8) (pt -3.925 -2.8) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -3.925 -2.8) (pt -3.925 2.8) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.2 2.5) (pt 2.2 2.5) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 2.2 2.5) (pt 2.2 -2.5) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 2.2 -2.5) (pt -2.2 -2.5) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.2 -2.5) (pt -2.2 2.5) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.2 1.85) (pt -1.55 2.5) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.85 2.5) (pt 1.85 2.5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 1.85 2.5) (pt 1.85 -2.5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 1.85 -2.5) (pt -1.85 -2.5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.85 -2.5) (pt -1.85 2.5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.675 2.525) (pt -2.2 2.525) (width 0.2))
		)
	)
	(symbolDef "TLV6004IPWR" (originalName "TLV6004IPWR")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 4) (pt 0 mils -300 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -325 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 5) (pt 0 mils -400 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -425 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 6) (pt 0 mils -500 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -525 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 7) (pt 0 mils -600 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -625 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 8) (pt 1200 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 970 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 9) (pt 1200 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 970 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 10) (pt 1200 mils -200 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 970 mils -225 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 11) (pt 1200 mils -300 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 970 mils -325 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 12) (pt 1200 mils -400 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 970 mils -425 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 13) (pt 1200 mils -500 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 970 mils -525 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 14) (pt 1200 mils -600 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 970 mils -625 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 1000 mils 100 mils) (width 6 mils))
		(line (pt 1000 mils 100 mils) (pt 1000 mils -700 mils) (width 6 mils))
		(line (pt 1000 mils -700 mils) (pt 200 mils -700 mils) (width 6 mils))
		(line (pt 200 mils -700 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 1050 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 1050 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "TLV6004IPWR" (originalName "TLV6004IPWR") (compHeader (numPins 14) (numParts 1) (refDesPrefix IC)
		)
		(compPin "1" (pinName "OUT A") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "-IN A") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "3" (pinName "+IN A") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "4" (pinName "V+") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "5" (pinName "+IN B") (partNum 1) (symPinNum 5) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "6" (pinName "-IN B") (partNum 1) (symPinNum 6) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "7" (pinName "OUT B") (partNum 1) (symPinNum 7) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "14" (pinName "OUT D") (partNum 1) (symPinNum 8) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "13" (pinName "-IN D") (partNum 1) (symPinNum 9) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "12" (pinName "+IN D") (partNum 1) (symPinNum 10) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "11" (pinName "V-") (partNum 1) (symPinNum 11) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "10" (pinName "+IN C") (partNum 1) (symPinNum 12) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "9" (pinName "-IN C") (partNum 1) (symPinNum 13) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "8" (pinName "OUT C") (partNum 1) (symPinNum 14) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "TLV6004IPWR"))
		(attachedPattern (patternNum 1) (patternName "SOP65P640X120-14N")
			(numPads 14)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
				(padNum 5) (compPinRef "5")
				(padNum 6) (compPinRef "6")
				(padNum 7) (compPinRef "7")
				(padNum 8) (compPinRef "8")
				(padNum 9) (compPinRef "9")
				(padNum 10) (compPinRef "10")
				(padNum 11) (compPinRef "11")
				(padNum 12) (compPinRef "12")
				(padNum 13) (compPinRef "13")
				(padNum 14) (compPinRef "14")
			)
		)
		(attr "TI store Part Number" "TLV6004IPWR")
		(attr "Manufacturer_Name" "Texas Instruments")
		(attr "Manufacturer_Part_Number" "TLV6004IPWR")
		(attr "Description" "Operational Amplifiers - Op Amps 1-MHz, Low-Power Operational Amplifier for Cost-Sensitive Systems 14-TSSOP -40 to 125")
		(attr "<Hyperlink>" "http://www.ti.com/lit/gpn/tlv6004")
		(attr "<Component Height>" "1.2")
		(attr "<STEP Filename>" "TLV6004IPWR.stp")
	)

)
