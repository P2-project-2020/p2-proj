#include "view/PDF/pdfFactory.h"

#include<QFile>
#include<QTextDocument>
#include <QPrinter>
#include <QPainter>
#include <QMessageBox>
#include <QDate>

#include <QDebug>

#include <view/PDF/tablePrinter.h>

#include "model/hierarchy/strumento.h"

PdfFactory::PdfFactory(QAbstractTableModel *magazzino, QAbstractTableModel *carrello, Model *core):
    magazzinoAdapter(magazzino),
    carrelloAdapter(carrello),
    model(core)
{

}

bool PdfFactory::printTable(int pagina,QString filename)
{

        QPrinter printer;//(QPrinter::HighResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                    printer.setPageOrientation(QPageLayout::Landscape);
                    printer.setOutputFileName(filename);
                   // printer.setPageMargins(12, 16, 12, 20, QPrinter::Millimeter);
                   //printer.setFullPage(false);

            // printer setup

            QPainter painter;
                    painter.begin(&printer);
                    /*
                    QImage img(":/images/res/logo.png");
                    painter.drawImage(QPoint(0,0),img);
                    painter.restore(); */

                    //Stampa tabella
                    TablePrinter tablePrinter(&painter, &printer);
                    QVector<int> columnStretch = QVector<int>() << 10 << 10 << 10 << 10 << 10 << 10 << 10 <<10 << 4;
                     if(pagina ==0){
                         if(!tablePrinter.printTable(magazzinoAdapter, columnStretch))
                             qDebug() << tablePrinter.lastError();
                     }else
                            if(pagina == 1){
                                if(!tablePrinter.printTable(carrelloAdapter, columnStretch))
                                    qDebug() << tablePrinter.lastError();
                         }

                    painter.end();
                    return true;

    }//printPdfTable


bool PdfFactory::printReceipt(QString filename){

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(filename);

    QTextDocument doc;

    QString finalCss;
    QFile baseCssFile(":/style/style/receiptcss.css");
    if (baseCssFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        finalCss.append(baseCssFile.readAll().data());
    }

    doc.setDefaultStyleSheet("#table{width:100%; display: block;} #table table{display: block; width: 100%;} #invoice-POS{box-shadow:0 0 1in -.25in rgba(0,0,0,.5);padding:2mm;margin:0 auto;width:44mm;background:#fff}#invoice-POS ::selection{background:#f31544;color:#fff}#invoice-POS ::moz-selection{background:#f31544;color:#fff}#invoice-POS h1{font-size:1.5em;color:#222}#invoice-POS h2{font-size:.9em}#invoice-POS h3{font-size:1.2em;font-weight:300;line-height:2em}#invoice-POS p{font-size:.7em;color:#666;line-height:1.2em}#invoice-POS #bot,#invoice-POS #mid,#invoice-POS #top{border-bottom:1px solid #eee}#invoice-POS #top{min-height:100px}#invoice-POS #mid{min-height:80px}#invoice-POS #bot{min-height:50px}#invoice-POS #top .logo{height:60px;width:60px;background:url(:/images/res/logo.png) no-repeat;background-size:60px 60px}#invoice-POS .clientlogo{float:left;height:60px;width:60px;background:url(:/images/res/logo.png) no-repeat;background-size:60px 60px;border-radius:50px}#invoice-POS .info{display:block;margin-left:0}#invoice-POS .title{float:right}#invoice-POS .title p{text-align:right}#invoice-POS table{width:100%;border-collapse:collapse}#invoice-POS .tabletitle{font-size:.5em;background:#eee}#invoice-POS .service{border-bottom:1px solid #eee}#invoice-POS .item{width:24mm}#invoice-POS .itemtext{font-size:.5em}#invoice-POS #legalcopy{margin-top:5mm}");
    QString html = "<div id='invoice-POS'><center id='top'> \
            <div class='info'> \
              <h2>QMusicShop</h2> \
               <h3> Ricevuta del: " + QDate::currentDate().toString("dd/MM/yyyy") + "</h3> \
            </div><!--End Info--> \
          </center><!--End InvoiceTop--> \
          \
          <div id='mid'> \
            <div class='info'> \
              <h2>Contact Info</h2> \
              <div> \
                 <p> <b>Address</b> : Via Trieste 63, 35121 Padova(PD) </p> \
                <p>  <b> Email </b>  : erik.nucibella@studenti.unipd.it , simonefederico.bergamin@studenti.unipd.it, luca.zaninotto.1@studenti.unipd.it </p> \
                 <p> <b>Phone </b>  : + 555-555-5555</p> \
              </div> \
            </div> \
          </div><!--End Invoice Mid--> \
          \
          <div id='bot'> \
                            <center>\
                          <div id='table'> \
                              <table> \
                                  <tr class='tabletitle'> \
                                      <td class='item'><h2>Item</h2></td> \
                                      <td class='Hours'><h2>Qty</h2></td> \
                                      <td class='Rate'><h2>Sub Total</h2></td> \
                                  </tr>";


            double totalAmount = 0;


            for(auto it = model->carrello_begin();it!=model->carrello_end(); ++it){

                Strumento *instrument = *it;
                QString item = QString::fromStdString(instrument->className() + " " + instrument->getBrand() + " " + instrument->getModel());
                unsigned int quantity = instrument->getQuantity();
                double price = instrument->getPrice();
                totalAmount += price*quantity;

                 html += "<tr class='service'> \
                    <td class='tableitem'><p class='itemtext'>" + item + "</p></td> \
                    <td class='tableitem'><p class='itemtext'>" + QString::number(quantity) + "</p></td> \
                    <td class='tableitem'><p class='itemtext'>" + QString::number(price) + "</p></td> \
                </tr>";


            }


            html += "<tr class='tabletitle'> \
                        <td></td> \
                        <td class='Rate'><h2>Total</h2></td> \
                        <td class='payment'><h2>" + QString::number(totalAmount) + " € </h2></td> \
                    </tr> \
                </table> \
                </center> \
            </div><!--End Table--> \
        </div><!--End InvoiceBot-->\
</div><!--End Invoice--> \
";
	    
             doc.setHtml(html);
	     
                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                doc.print(&printer);
		return true;
		 
}

