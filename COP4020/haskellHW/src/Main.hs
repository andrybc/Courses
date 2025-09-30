{-
  COP 4020 – Haskell Assignment: Calculating pi
  Author: Andry Canel
  PID:4262970

  What this program does:
    Implements five classic pi-approximation methods and prints their results:
      (a) Short Pi  = 4 * atan 1
      (b) Simple Pi = Leibniz (Madhava–Leibniz) alternating series
      (c) Wells Pi  = Nilakantha series (fast alternating correction to 3)
      (d) Euler Pi  = Basel-related sum  pi ≈ sqrt(6 * Σ 1/n^2)
      (e) Wallis    = Wallis product  pi/2 = Π (4n^2)/(4n^2 - 1)

    All methods except Short Pi iterate 200 terms as required.

  Online compiler link:
    https://play.haskell.org/

-}

module Main where

-- Number of terms (except Short Pi which uses a closed form with atan)
terms :: Int
terms = 200

------------------------------------------------------------------------------
-- (a) Short Pi
-- Definition: π = 4 * arctan(1)
-- atan :: Floating a => a -> a  (from Prelude)
shortPi :: Double
shortPi = 4 * atan 1

------------------------------------------------------------------------------
-- Utility: harmonic-of-squares partial sum  H2(n) = Σ_{k=1..n} 1/k^2
-- (The assignment hint mentioned that computing 1/n^2 can help.)
h2 :: Int -> Double
h2 n = sum [ 1 / fromIntegral (k * k) | k <- [1 .. n] ]

------------------------------------------------------------------------------
-- (b) Simple Pi  (Leibniz / Gregory series)
-- π/4 = 1 - 1/3 + 1/5 - 1/7 + ... = Σ_{k=0..∞} (-1)^k / (2k+1)
-- We take the first n terms (k = 0..n-1).
simplePi :: Int -> Double
simplePi n =
  4 * sum [ ((-1) ** fromIntegral k) / fromIntegral (2 * k + 1)
          | k <- [0 .. n - 1]
          ]

------------------------------------------------------------------------------
-- (c) Wells Pi  (using the Nilakantha series, fast alternating series)
-- π = 3 + 4/(2·3·4) − 4/(4·5·6) + 4/(6·7·8) − ...
-- Term k (starting at k=1) is:  sign * 4 / ( (2k)*(2k+1)*(2k+2) )
-- where sign alternates +, −, +, −, ...
wellsPi :: Int -> Double
wellsPi n = 3 + sum [ term k | k <- [1 .. n] ]
  where
    term k =
      let a = fromIntegral (2 * k)       -- 2k
          b = a + 1                       -- 2k + 1
          c = a + 2                       -- 2k + 2
          base = 4 / (a * b * c)
          sgn  = if odd k then 1 else -1  -- +, -, +, -, ...
      in  fromIntegral sgn * base

------------------------------------------------------------------------------
-- (d) Euler Pi  (Basel-problem relation)
-- Euler showed Σ_{n=1..∞} 1/n^2 = π^2 / 6  ⇒  π = sqrt(6 * Σ 1/n^2)
-- Using the first n terms gives a decent approximation.
eulerPi :: Int -> Double
eulerPi n = sqrt (6 * h2 n)

------------------------------------------------------------------------------
-- (e) Wallis formula (product)
-- π/2 = Π_{n=1..∞} (4n^2) / (4n^2 - 1)
-- ⇒ π ≈ 2 * Π_{n=1..N} (4n^2)/(4n^2 - 1)
wallisPi :: Int -> Double
wallisPi n = 2 * product
  [ (4 * x * x) / (4 * x * x - 1)
  | k <- [1 .. n]
  , let x = fromIntegral k
  ]

------------------------------------------------------------------------------
-- Pretty print with fixed decimals (optional helper)
format :: Double -> String
format x = showFFloat 12 x
  where
    -- minimal local formatter to avoid importing Numeric
    showFFloat :: Int -> Double -> String
    showFFloat d v =
      let s  = show v
      in  case break (=='.') s of
            (a, [])     -> a ++ "." ++ replicate d '0'
            (a, _:rest) ->
              let needed = max 0 (d - length rest)
              in  a ++ "." ++ take d (rest ++ replicate needed '0')

main :: IO ()
main = do
  putStrLn "Simple Pi"
  print (simplePi terms)

  putStrLn "Wells Pi"
  print (wellsPi terms)

  putStrLn "short Pi"
  print shortPi

  putStrLn "euler Pi"
  print (eulerPi terms)

  putStrLn "wallisSum Pi"
  print (wallisPi terms)

  {-
    Required comment (answer):
    Apart from Short Pi, which method gives the most precise output at 200 terms?

    Answer (with n = 200): Wells Pi (Nilakantha series) produced the smallest
    absolute error compared to Prelude `pi` in my tests, outperforming the
    Simple (Leibniz), Euler (Basel partial sum), and Wallis product methods.
  -}
