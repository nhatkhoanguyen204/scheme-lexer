(define r #f)

(+ 1 (call/cc (lambda (cont)
                (set! r cont)
                (+ 2 3))))

(r 10)

(exit)