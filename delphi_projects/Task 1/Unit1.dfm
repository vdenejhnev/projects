object Form1: TForm1
  Left = 500
  Top = 124
  Width = 1019
  Height = 540
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object strngrd1: TStringGrid
    Left = 104
    Top = 72
    Width = 817
    Height = 209
    ColCount = 8
    FixedCols = 0
    RowCount = 2
    TabOrder = 0
    ColWidths = (
      124
      105
      64
      64
      100
      102
      98
      95)
  end
  object btn1: TBitBtn
    Left = 112
    Top = 304
    Width = 161
    Height = 33
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1092#1072#1081#1083
    TabOrder = 1
    OnClick = btn1Click
  end
  object btn2: TBitBtn
    Left = 296
    Top = 304
    Width = 161
    Height = 33
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1092#1072#1081#1083
    TabOrder = 2
    OnClick = btn1Click
  end
  object btn3: TBitBtn
    Left = 480
    Top = 304
    Width = 161
    Height = 33
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 3
    OnClick = btn1Click
  end
  object edt1: TEdit
    Left = 360
    Top = 392
    Width = 329
    Height = 21
    TabOrder = 4
    Text = 'edt1'
  end
end
